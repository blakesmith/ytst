#include "sig.h"

namespace ev {
	Signal::Signal(Loop& loop, void(*cb)(EV_P_ struct ev_signal *s, int revents), int sigs) : loop(loop) {
		ev_signal_init(&sig, cb, sigs);
	}

	Signal::~Signal() {
		stop();
	}

	void Signal::start() {
		ev_signal_start(loop.get(), &sig);
	}

	void Signal::stop() {
		ev_signal_stop(loop.get(), &sig);
	}

	void Signal::set_data(void *data) {
		sig.data = data;
	}
}
