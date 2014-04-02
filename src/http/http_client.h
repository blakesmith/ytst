#ifndef YTST_HTTP_CLIENT_HPP
#define YTST_HTTP_CLIENT_HPP

extern "C" {
#include <ev.h>
}

#include <list>
#include <memory>

#include "http_parser.h"
#include "http_handler.h"
#include "http_response_writer.h"
#include "buffer.h"
#include "ev_io.h"
#include "ev_async.h"
#include "socket_desc.h"

namespace ytst {
	class HttpClient {
	private:
		SocketDesc sd;

		HttpRequest request;
		HttpParser parser;
		HttpResponseWriter writer;

		struct ev_loop *loop;
		EvAsync notify;
		EvIo io;
		std::queue<std::shared_ptr<Buffer>> write_queue;

		std::unique_ptr<HttpHandler> handler;

		bool headers_sent;

		static void io_cb(struct ev_loop *loop, ev_io *watcher, int revents);
		static void notify_cb(struct ev_loop *loop, ev_async *watcher, int revents);
		void notify_callback(struct ev_loop *loop, ev_async *watcher, int revents);
		void callback(struct ev_loop *loop, ev_io *watcher, int revents);
		void write_cb(ev_io *watcher);
		void read_cb(ev_io *watcher);
		void start_decode(std::string& youtube_id);
		virtual ~HttpClient();
	public:
		HttpClient(std::unique_ptr<HttpHandler> handler,
			   struct ev_loop *loop,
			   int s);
	};
}
#endif
