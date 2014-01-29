#ifndef YTST_HTTP_CLIENT_HPP
#define YTST_HTTP_CLIENT_HPP

#include <ev++.h>
#include <list>
#include <thread>
#include <memory>
#include <atomic>

#include "HttpParser.hpp"
#include "Python.hpp"
#include "HttpResponseWriter.hpp"
#include "Stream.hpp"
#include "Buffer.hpp"

namespace ytst {
	class HttpClient {
	private:
		HttpRequest request;
		HttpParser parser;
		std::string fifo_directory;
		std::shared_ptr<ytst::Python> python;
		HttpResponseWriter writer;
		std::thread stream_thread;
		std::atomic<bool> stream_running;

		struct ev_loop *loop;
		ev_io io;
		ev_async notify;
		int sfd;
		std::queue<std::shared_ptr<Buffer>> write_queue;

		bool headers_sent;

		static void io_cb(struct ev_loop *loop, ev_io *watcher, int revents);
		static void notify_cb(struct ev_loop *loop, ev_async *watcher, int revents);
		void notify_callback(struct ev_loop *loop, ev_async *watcher, int revents);
		void callback(struct ev_loop *loop, ev_io *watcher, int revents);
		void write_cb(ev_io *watcher);
		void read_cb(ev_io *watcher);
		void start_decode(std::string& youtube_id);
		void io_reset(int mode);
		virtual ~HttpClient();
	public:
		HttpClient(std::string fifo_directory,
			   std::shared_ptr<ytst::Python> python,
			   struct ev_loop *loop,
			   int s);
	};
}
#endif
