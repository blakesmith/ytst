#ifndef YTST_HTTP_SERVER_HPP
#define YTST_HTTP_SERVER_HPP

#include <ev++.h>
#include <netinet/in.h>
#include <sys/socket.h>

namespace ytst {
	class HttpServer {
	private:
		struct ev_io io;
		struct ev_signal sio;
		struct ev_loop *loop;
		int s;
	public:
		static void io_accept(struct ev_loop *loop, ev_io *watcher, int revents);
		static void signal_cb(struct ev_loop *loop, ev_signal *signal, int revents);
		void start();
		HttpServer(int port);
		~HttpServer();
	};
}
#endif
