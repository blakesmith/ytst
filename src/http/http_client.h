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
#include "socket_desc.h"

#include "ev/io.h"
#include "ev/async.h"

#define READ_BUFFER_SIZE 1024

namespace ytst {
	class HttpClient {
	private:
		SocketDesc sd;
		std::queue<std::shared_ptr<Buffer>> write_queue;

		HttpRequest request;
		HttpParser parser;
		HttpResponseWriter writer;

		ev::Loop& loop;
		ev::Async notify;
		ev::Io io;

		std::unique_ptr<HttpHandler> handler;

		char read_buffer[READ_BUFFER_SIZE];
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
			   ev::Loop& loop,
			   int s);
	};
}
#endif
