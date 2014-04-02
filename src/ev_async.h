#ifndef YTST_EV_ASYNC_H
#define YTST_EV_ASYNC_H

#include <ev.h>

namespace ytst {
	class EvAsync {
		struct ev_loop *loop;
		ev_async async;
	public:
		EvAsync(struct ev_loop *loop, void(*cb)(EV_P_ struct ev_async *a, int revents));
		void start();
		void send();
		void set_data(void *data);
				 
		EvAsync(const EvAsync& other) = delete;
		EvAsync(EvAsync&& other) = delete;
		EvAsync& operator=(EvAsync&& other) = delete;
		EvAsync& operator=(EvAsync other) = delete;
		~EvAsync();
	};
}

#endif
