#include <fcntl.h>
#include <unistd.h>

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
			perror("Got invalid event");
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
		Buffer* buf = writer->get_buffer();
		write_queue.push_back(buf);
		ev_io_stop(loop, &io);
		ev_io_set(&io, io.fd, EV_WRITE);
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
			perror("Read error");
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
			perror("Read error");
			return;
		}

		if (nread == 0) {
			delete this;
		} else {
			write_queue.push_back(new Buffer(buffer, nread));
		}
	}

	HttpClient::~HttpClient() {
		ev_io_stop(loop, &io);
		close(sfd);
		printf("Client disconnected\n");
	}

	HttpClient::HttpClient(std::string fifo_directory,
			       std::shared_ptr<ytst::Python> python,
			       struct ev_loop *loop,
			       int s) : fifo_directory(fifo_directory),
					python(python),
					loop(loop),
					sfd(s) {
		
		fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK);
		printf("Got connection\n");

		io.data = (void *)this;
		notify.data = (void *)this;

		ev_async_init(&notify, HttpClient::notify_cb);
		ev_io_init(&io, HttpClient::io_cb, s, EV_READ);
		ev_io_start(loop, &io);

		ytst::BufferedWriter wr([=] {
				ev_async_send(loop, &notify);
			});
		writer = &wr;

		ytst::Stream strm(fifo_directory, python, writer);
		stream = &strm;
		stream_thread = std::thread([=] { stream->stream("lTx3G6h2xyA"); });
	}
}

