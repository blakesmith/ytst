#include <fcntl.h>
#include <unistd.h>

#include "HttpServer.hpp"
#include "HttpClient.hpp"

namespace ytst {
	void HttpServer::io_accept(struct ev_loop *loop, ev_io *watcher, int revents) {
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

		new HttpClient(loop, client_sd);
	}

	void HttpServer::signal_cb(struct ev_loop *loop, ev_signal *signal, int revents) {
		ev_break(loop, EVBREAK_ALL);
	}

	void HttpServer::start() {
		ev_loop(loop, 0);
	}

	HttpServer::HttpServer(int port) {
		printf("Listening on port %d\n", port);

		struct sockaddr_in addr;
		
		s = socket(PF_INET, SOCK_STREAM, 0);

		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		addr.sin_addr.s_addr = INADDR_ANY;

		if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
			perror("Failed to bind to port.\n");
		}

		fcntl(s, F_SETFL, fcntl(s, F_GETFL, 0) | O_NONBLOCK);

		listen(s, 5);

		loop = ev_default_loop(0);

		ev_io_init(&io, HttpServer::io_accept, s, EV_READ);
		ev_io_start(loop, &io);

		ev_signal_init(&sio, HttpServer::signal_cb, SIGINT);
		ev_signal_start(loop, &sio);
	}

	HttpServer::~HttpServer() {
		shutdown(s, SHUT_RDWR);
		close(s);
	}
}

