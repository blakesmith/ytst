#ifndef YTST_EV_ASYNC_H
#define YTST_EV_ASYNC_H

#include <ev.h>

namespace ev {
	class Async {
		struct ev_loop *loop;
		ev_async async;
	public:
		Async(struct ev_loop *loop, void(*cb)(EV_P_ struct ev_async *a, int revents));
		void start();
		void stop();
		void send();
		void set_data(void *data);
				 
		Async(const Async& other) = delete;
		Async(Async&& other) = delete;
		Async& operator=(Async&& other) = delete;
		Async& operator=(Async other) = delete;
		~Async();
	};
}

#endif
