#include "io.h"

namespace ev {
	Io::Io(Loop& loop, void(*cb)(EV_P_ struct ev_io *a, int revents), int sd) : loop(loop)
	{
		ev_io_init(&io, cb, sd, EV_READ);
	}

	Io::~Io() {
		stop();
	}

	void Io::start() {
		ev_io_start(loop.get(), &io);
	}

	void Io::stop() {
		ev_io_stop(loop.get(), &io);
	}

	void Io::set(int mode) {
		ev_io_set(&io, io.fd, mode);
	}

	void Io::reset(int mode) {
		stop();
		set(mode);
		start();
	}

	void Io::set_data(void *data) {
		io.data = data;
	}
}

