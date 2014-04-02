#include "ev_async.h"

namespace ytst {
	EvAsync::EvAsync(struct ev_loop *loop, void(*cb)(EV_P_ struct ev_async *a, int revents)) : loop(loop)
	{
		ev_async_init(&async, cb);
	}

	EvAsync::~EvAsync() {
		ev_async_stop(loop, &async);
	}

	void EvAsync::start() {
		ev_async_start(loop, &async);
	}

	void EvAsync::send() {
		ev_async_send(loop, &async);
	}

	void EvAsync::set_data(void *data) {
		async.data = data;
	}
}

