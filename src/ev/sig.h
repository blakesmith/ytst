#ifndef YTST_EV_SIGNAL_H
#define YTST_EV_SIGNAL_H

#include <ev.h>

#include "loop.h"

namespace ev {
	class Signal {
		Loop& loop;
		struct ev_signal sig;
	public:
		Signal(Loop& loop, void(*cb)(EV_P_ struct ev_signal *a, int revents), int sigs);
		void start();
		void stop();
		void set_data(void *data);
				 
		Signal(const Signal& other) = delete;
		Signal(Signal&& other) = delete;
		Signal& operator=(Signal&& other) = delete;
		Signal& operator=(Signal other) = delete;
		~Signal();
	};
}

#endif
