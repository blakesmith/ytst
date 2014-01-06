#ifndef YTST_HTTP_CLIENT_HPP
#define YTST_HTTP_CLIENT_HPP

#include <ev++.h>
#include <list>

#include "Buffer.hpp"

namespace ytst {
	class HttpClient {
	private:
		struct ev_loop *loop;
		ev_io io;
		int sfd;
		std::list<Buffer*> write_queue;

		static void cb(struct ev_loop *loop, ev_io *watcher, int revents);
		void callback(struct ev_loop *loop, ev_io *watcher, int revents);
		void write_cb(ev_io *watcher);
		void read_cb(ev_io *watcher);
		virtual ~HttpClient();
	public:
		HttpClient(struct ev_loop *loop, int s);
	};
}
#endif
