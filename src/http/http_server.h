#ifndef YTST_HTTP_SERVER_HPP
#define YTST_HTTP_SERVER_HPP

#include <ev++.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <memory>

#include "cmd_opt.h"
#include "http_handler.h"
#include "ev/loop.h"
#include "ev/io.h"
#include "ev/sig.h"

namespace ytst {
	class HttpServer {
	private:
		const Options& options;
		int sock;
		ev::Loop loop;
		ev::Signal sio;
		ev::Io io;

		int s;
		std::function<std::unique_ptr<HttpHandler>()> make_handler;

		void accept_cb(struct ev_loop *loop, ev_io *watcher, int revents);
	public:
		static void io_accept(struct ev_loop *loop, ev_io *watcher, int revents);
		static void signal_cb(struct ev_loop *loop, ev_signal *signal, int revents);
		void set_handler(std::function<std::unique_ptr<HttpHandler>()>);
		void start();
		void stop();
		HttpServer(const Options& options);
		~HttpServer();
	};
}
#endif
