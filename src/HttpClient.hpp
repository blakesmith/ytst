#ifndef YTST_HTTP_CLIENT_HPP
#define YTST_HTTP_CLIENT_HPP

#include <ev++.h>
#include <list>
#include <thread>
#include <memory>

#include "Python.hpp"
#include "BufferedWriter.hpp"
#include "Stream.hpp"
#include "Buffer.hpp"

namespace ytst {
	class HttpClient {
	private:
		std::string fifo_directory;
		std::shared_ptr<ytst::Python> python;
		BufferedWriter writer;
		std::thread stream_thread;

		struct ev_loop *loop;
		ev_io io;
		ev_async notify;
		int sfd;
		std::list<Buffer*> write_queue;

		bool headers_sent = false;

		static void io_cb(struct ev_loop *loop, ev_io *watcher, int revents);
		static void notify_cb(struct ev_loop *loop, ev_async *watcher, int revents);
		void notify_callback(struct ev_loop *loop, ev_async *watcher, int revents);
		void callback(struct ev_loop *loop, ev_io *watcher, int revents);
		void write_cb(ev_io *watcher);
		void read_cb(ev_io *watcher);
		virtual ~HttpClient();
	public:
		HttpClient(std::string fifo_directory,
			   std::shared_ptr<ytst::Python> python,
			   struct ev_loop *loop,
			   int s);
	};
}
#endif
