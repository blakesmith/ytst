#include "async.h"

namespace ev {
	Async::Async(Loop& loop, void(*cb)(EV_P_ struct ev_async *a, int revents)) : loop(loop)
	{
		ev_async_init(&async, cb);
	}

	Async::~Async() {
		stop();
	}

	void Async::start() {
		ev_async_start(loop.get(), &async);
	}

	void Async::stop() {
		ev_async_stop(loop.get(), &async);
	}

	void Async::send() {
		ev_async_send(loop.get(), &async);
	}

	void Async::set_data(void *data) {
		async.data = data;
	}
}

