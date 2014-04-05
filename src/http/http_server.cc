#include <fcntl.h>
#include <iostream>
#include <unistd.h>

#include "log.h"
#include "http_server.h"
#include "http_client.h"

namespace ytst {
	void HttpServer::io_accept(struct ev_loop *l, ev_io *watcher, int revents) {
		HttpServer* impl = reinterpret_cast<HttpServer*>(watcher->data);
		impl->accept_cb(l, watcher, revents);
	}

	void HttpServer::signal_cb(struct ev_loop *l, ev_signal *signal, int revents) {
		HttpServer* impl = reinterpret_cast<HttpServer*>(signal->data);
		impl->stop();
	}

	void HttpServer::accept_cb(struct ev_loop *l, ev_io *watcher, int revents) {
		if (EV_ERROR & revents) {
			perror("Got invalid event.\n");
			return;
		}

		struct sockaddr_in client_addr;
		socklen_t client_len = sizeof(client_addr);

		int client_sd = accept(watcher->fd, (struct sockaddr *)&client_addr, &client_len);
		if (client_sd < 0) {
			perror("Accept error\n");
			return;
		}

		new HttpClient(make_handler(), loop, client_sd);
	}

	void HttpServer::start() {
		sio.start();
		io.start();
		loop.start();
	}

	void HttpServer::stop() {
		loop.stop();
	}

	void HttpServer::set_handler(std::function<std::unique_ptr<HttpHandler>()> handler) {
		make_handler = handler;
	}

	static int listen_socket(const Options& options) {
		int s;
		struct sockaddr_in addr;

		s = socket(PF_INET, SOCK_STREAM, 0);
		
		addr.sin_family = AF_INET;
		addr.sin_port = htons(options.listen_port);
		addr.sin_addr.s_addr = INADDR_ANY;

		if (::bind(s, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
			perror("Failed to bind to port.\n");
		}

		fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK);

		listen(s, 5);

		LOG(logINFO) << "Listening on port " << options.listen_port;

		return s;
	}

	HttpServer::HttpServer(const Options& options) :
		options(options),
		sock(listen_socket(options)),
		sio(loop, signal_cb, SIGINT),
		io(loop, io_accept, sock) {

		io.set_data(reinterpret_cast<void*>(this));
		sio.set_data(reinterpret_cast<void*>(this));
	}

	HttpServer::~HttpServer() {
		shutdown(s, SHUT_RDWR);
		close(s);
	}
}

