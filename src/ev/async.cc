#include "async.h"

namespace ev {
	Async::Async(struct ev_loop *loop, void(*cb)(EV_P_ struct ev_async *a, int revents)) : loop(loop)
	{
		ev_async_init(&async, cb);
	}

	Async::~Async() {
		stop();
	}

	void Async::start() {
		ev_async_start(loop, &async);
	}

	void Async::stop() {
		ev_async_stop(loop, &async);
	}

	void Async::send() {
		ev_async_send(loop, &async);
	}

	void Async::set_data(void *data) {
		async.data = data;
	}
}

