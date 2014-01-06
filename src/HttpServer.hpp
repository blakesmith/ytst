#ifndef YTST_HTTP_SERVER_HPP
#define YTST_HTTP_SERVER_HPP

#include <ev++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <memory>

#include "CmdOpt.hpp"
#include "Python.hpp"

namespace ytst {
	class HttpServer {
	private:
		struct ev_io io;
		struct ev_signal sio;
		struct ev_loop *loop;
		int s;

		Options* options;
		std::shared_ptr<ytst::Python> python;

		void accept_cb(struct ev_loop *loop, ev_io *watcher, int revents);
	public:
		static void io_accept(struct ev_loop *loop, ev_io *watcher, int revents);
		static void signal_cb(struct ev_loop *loop, ev_signal *signal, int revents);
		void start();
		HttpServer(Options* options);
		~HttpServer();
	};
}
#endif
