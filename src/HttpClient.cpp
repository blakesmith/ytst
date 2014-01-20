#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "Log.hpp"
#include "HttpClient.hpp"

#define READ_BUFFER_SIZE 1024

namespace ytst {
	void HttpClient::io_cb(struct ev_loop *loop, ev_io *watcher, int revents) {
		HttpClient *inst = (HttpClient *)watcher->data;
		inst->callback(loop, watcher, revents);
	}
	
	void HttpClient::notify_cb(struct ev_loop *loop, ev_async *watcher, int revents) {
		HttpClient *inst = (HttpClient *)watcher->data;
		inst->notify_callback(loop, watcher, revents);
	}

	void HttpClient::callback(struct ev_loop *loop, ev_io *watcher, int revents) {
		if (EV_ERROR & revents) {
			LOG(logWARNING) << "Got invalid event: " << strerror(errno);
			return;
		}

		if (EV_READ & revents) {
			read_cb(watcher);
		}
		
		if (EV_WRITE & revents) {
			write_cb(watcher);
		}

		if (write_queue.empty()) {
			io_reset(EV_READ);
		} else {
			io_reset(EV_READ | EV_WRITE);
		}
	}

	void HttpClient::notify_callback(struct ev_loop *loop, ev_async *watcher, int revents) {
		auto buf = writer.get_buffer();
		write_queue.push(buf);
		io_reset(EV_WRITE);
		if (writer.has_buffer()) {
			ev_async_send(loop, &notify);
		}
	}

	void HttpClient::write_cb(ev_io *watcher) {
		if (write_queue.empty()) {
			io_reset(EV_READ);
			return;
		}
		auto buffer = write_queue.front();

		ssize_t written = write(watcher->fd,
					buffer->dpos(),
					buffer->nbytes());
		if (written < 0) {
			LOG(logWARNING) << "Write error: " << strerror(errno);
			return;
		}

		buffer->pos += written;
		if (buffer->nbytes() == 0) {
			write_queue.pop();
		}
	}

	void HttpClient::read_cb(ev_io *watcher) {
		char buffer[READ_BUFFER_SIZE];
		ssize_t nread = recv(watcher->fd, buffer, READ_BUFFER_SIZE-1, 0);
		buffer[nread+1] = '\0';

		if (nread < 0) {
			LOG(logWARNING) << "Read error: " << strerror(errno);
			return;
		}

		if (nread == 0) {
			delete this;
		}
		
		if (!headers_sent) {
			LOG(logDEBUG) << "Parse HTTP request";
			parser.execute(&request, buffer, nread+1, 0);
			if (parser.is_finished()) {
				LOG(logDEBUG) << "Parse HTTP request finished";
				map<string, string> query;
				HttpParser::parse_query(query, request.query_string);
				for (auto& h : request.headers) {
					LOG(logDEBUG) << "Header: " << h.first << ", " << h.second;
				}
				LOG(logDEBUG) << request.http_version;
				auto youtube_id = query.find("id");
				if (youtube_id == query.end()) {
					std::string body = "Must pass youtube video id as query param 'id'";
					writer.write_response(400, false, body);
					headers_sent = true;
				} else {
					writer.header["Content-Type"] = "audio/mpeg";
					writer.header["icy-br"] = "128";
					writer.write_header(200, false, -1);
					start_decode(youtube_id->second);
					headers_sent = true;
				}
			}
		}
	}

	void HttpClient::start_decode(std::string& youtube_id) {
		LOG(logINFO) << "Starting stream thread";
		stream_thread = std::thread([=] {
				ytst::Stream stream(this->fifo_directory,
						    this->python,
						    &writer);
				stream.stream(youtube_id);
			});
	}

	void HttpClient::io_reset(int mode) {
		ev_io_stop(loop, &io);
		ev_io_set(&io, io.fd, mode);
		ev_io_start(loop, &io);
	}

	HttpClient::~HttpClient() {
		if (stream_thread.joinable()) {
			stream_thread.join();
		}
		ev_io_stop(loop, &io);
		ev_async_stop(loop, &notify);
		close(sfd);
		LOG(logINFO) << "Client disconnected";
	}

	HttpClient::HttpClient(std::string fifo_directory,
			       std::shared_ptr<ytst::Python> python,
			       struct ev_loop *loop,
			       int s) : loop(loop),
					sfd(s) {
		this->fifo_directory = fifo_directory;
		this->python = python;

		headers_sent = false;

		fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK);
		LOG(logINFO) << "Got connection";

		io.data = reinterpret_cast<void *>(this);
		notify.data = reinterpret_cast<void *>(this);

		ev_async_init(&notify, notify_cb);

		writer.add_callback([=] {
				ev_async_send(loop, &notify);
			});

		ev_async_start(loop, &notify);

		ev_io_init(&io, io_cb, s, EV_READ);
		ev_io_start(loop, &io);
	}
}

