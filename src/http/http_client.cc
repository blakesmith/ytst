#include <fcntl.h>
#include <iostream>

#include "log.h"
#include "http_client.h"

namespace ytst {
	void HttpClient::io_cb(struct ev_loop *loop, ev_io *watcher, int revents) {
		HttpClient *inst = reinterpret_cast<HttpClient*>(watcher->data);
		inst->callback(loop, watcher, revents);
	}
	
	void HttpClient::notify_cb(struct ev_loop *loop, ev_async *watcher, int revents) {
		HttpClient *inst = reinterpret_cast<HttpClient*>(watcher->data);
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
			io.reset(EV_READ);
		} else {
			io.reset(EV_READ | EV_WRITE);
		}
	}

	void HttpClient::close() {
		LOG(logINFO) << "Closing HTTP connection";
		delete this;
	}

	void HttpClient::notify_callback(struct ev_loop *loop, ev_async *watcher, int revents) {
		while (writer.has_buffer()) {
			auto buf = writer.get_buffer();
			write_queue.push(buf);
		}

		io.reset(EV_WRITE);
	}

	void HttpClient::write_cb(ev_io *watcher) {
		if (write_queue.empty()) {
			io.reset(EV_READ);
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
		ssize_t nread = recv(watcher->fd, read_buffer, READ_BUFFER_SIZE-1, 0);
		read_buffer[nread+1] = '\0';

		if (nread < 0) {
			LOG(logWARNING) << "Read error: " << strerror(errno);
			return;
		}

		if (nread == 0) {
			close();
		}
		
		if (!parser.is_finished()) {
			LOG(logDEBUG) << "Parse HTTP request";
			parser.execute(&request, read_buffer, nread+1, 0);

			if (parser.has_error()) {
				LOG(logINFO) << "Invalid HTTP request";
				close();
			}

			if (parser.is_finished()) {
				LOG(logDEBUG) << "Parse HTTP request finished";
				writer.header["Connection"] = "close";
				handler->serve(request, writer);
				parser.reset();
			}
		}
	}

	HttpClient::~HttpClient() {
		LOG(logINFO) << "Client disconnected";
	}

	HttpClient::HttpClient(std::unique_ptr<HttpHandler> handler,
			       ev::Loop& loop,
			       int s) : 
		handler(std::move(handler)),
		loop(loop),
		sd(s),
		notify(loop, notify_cb),
		io(loop, io_cb, sd.get())
	{
		headers_sent = false;

		fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK);
		LOG(logINFO) << "Got connection";

		io.set_data(reinterpret_cast<void *>(this));
		notify.set_data(reinterpret_cast<void *>(this));

		writer.add_callback([=] {
				notify.send();
			});
		
		notify.start();
		io.start();
	}
}

