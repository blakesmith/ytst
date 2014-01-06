#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#include "Log.hpp"
#include "HttpClient.hpp"

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
			ev_io_stop(loop, &io);
			ev_io_set(&io, io.fd, EV_READ);
			ev_io_start(loop, &io);
		} else {
			ev_io_stop(loop, &io);
			ev_io_set(&io, io.fd, EV_READ | EV_WRITE);
			ev_io_start(loop, &io);
		}
	}

	void HttpClient::notify_callback(struct ev_loop *loop, ev_async *watcher, int revents) {
		Buffer* buf = writer.get_buffer();
		write_queue.push_back(buf);
		ev_io_stop(loop, &io);
		ev_io_set(&io, io.fd, EV_WRITE);
		ev_io_start(loop, &io);
	}

	void HttpClient::write_cb(ev_io *watcher) {
		if (write_queue.empty()) {
			ev_io_stop(loop, &io);
			ev_io_set(&io, io.fd, EV_READ);
			ev_io_start(loop, &io);
			return;
		}

		Buffer *buffer = write_queue.front();

		ssize_t written = write(watcher->fd, buffer->dpos(), buffer->nbytes());
		if (written < 0) {
			LOG(logWARNING) << "Write error: " << strerror(errno);
			return;
		}

		buffer->pos += written;
		if (buffer->nbytes() == 0) {
			write_queue.pop_front();
			delete buffer;
		}
	}

	void HttpClient::read_cb(ev_io *watcher) {
		char buffer[1024];
		ssize_t nread = recv(watcher->fd, buffer, sizeof(buffer), 0);

		if (nread < 0) {
			LOG(logWARNING) << "Read error: " << strerror(errno);
			return;
		}

		if (nread == 0) {
			write(watcher->fd, "\r\n", 2);
			delete this;
		} else {
			if (!headers_sent) {
				static const char* header =
					"HTTP/1.1 200 OK\r\n"
					"Content-Type: audio/mpeg\r\n"
					"Connection: close\r\n"
					"\r\n";
				write_queue.push_back(new Buffer(header, strlen(header)));
				headers_sent = true;
			}
		}
	}

	HttpClient::~HttpClient() {
		stream_thread.join();
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

		fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK);
		LOG(logINFO) << "Got connection";

		io.data = (void *)this;
		notify.data = (void *)this;

		ev_async_init(&notify, HttpClient::notify_cb);
		ev_async_start(loop, &notify);

		ev_io_init(&io, HttpClient::io_cb, s, EV_READ);
		ev_io_start(loop, &io);

		writer.add_callback([=] {
				ev_async_send(loop, &notify);
			});

		stream_thread = std::thread([=] {
				ytst::Stream stream(this->fifo_directory,
						    this->python, 
						    &writer);
				stream.stream("-5Ilq3kFxek");
			});
	}
}

