#include "loop.h"

namespace ev {
	Loop::Loop() {
		loop = ev_loop_new(EVFLAG_AUTO);
	}

	Loop::~Loop() {
		stop();
	}

	Loop::Loop(const Loop& other) {
		loop = other.loop;
	}

	Loop::Loop(Loop&& other) {
		loop = other.loop;
		other.loop = nullptr;
	}

	Loop& Loop::operator=(Loop other) {
		loop = other.loop;
		return *this;
	}
	
	Loop& Loop::operator=(Loop&& other) {
		loop = other.loop;
		other.loop = nullptr;
		return *this;
	}

	void Loop::stop() {
		ev_break(loop, EVBREAK_ALL);
	}

	void Loop::start() {
		ev_run(loop, 0);
	}
	
	struct ev_loop* Loop::get() const {
		return loop;
	}
}
