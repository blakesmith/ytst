#ifndef YTST_EV_IO_H
#define YTST_EV_IO_H

#include <ev.h>

namespace ev {
	class Io {
		struct ev_loop *loop;
		ev_io io;
	public:
		Io(struct ev_loop *loop, void(*cb)(EV_P_ struct ev_io *a, int revents), int sd);
		void start();
		void stop();
		void set(int mode);
		void reset(int mode);
		void set_data(void *data);
				 
		Io(const Io& other) = delete;
		Io(Io&& other) = delete;
		Io& operator=(Io&& other) = delete;
		Io& operator=(Io other) = delete;
		~Io();
	};
}

#endif
