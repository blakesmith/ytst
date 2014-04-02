#include "ev_io.h"

namespace ytst {
	EvIo::EvIo(struct ev_loop *loop, void(*cb)(EV_P_ struct ev_io *a, int revents), int sd) : loop(loop)
	{
		ev_io_init(&io, cb, sd, EV_READ);
	}

	EvIo::~EvIo() {
		stop();
	}

	void EvIo::start() {
		ev_io_start(loop, &io);
	}

	void EvIo::stop() {
		ev_io_stop(loop, &io);
	}

	void EvIo::set(int mode) {
		ev_io_set(&io, io.fd, mode);
	}

	void EvIo::reset(int mode) {
		stop();
		set(mode);
		start();
	}

	void EvIo::set_data(void *data) {
		io.data = data;
	}
}

