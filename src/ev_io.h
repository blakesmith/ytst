#ifndef YTST_EV_IO_H
#define YTST_EV_IO_H

#include <ev.h>

namespace ytst {
	class EvIo {
		struct ev_loop *loop;
		ev_io io;
	public:
		EvIo(struct ev_loop *loop, void(*cb)(EV_P_ struct ev_io *a, int revents), int sd);
		void start();
		void stop();
		void set(int mode);
		void reset(int mode);
		void set_data(void *data);
				 
		EvIo(const EvIo& other) = delete;
		EvIo(EvIo&& other) = delete;
		EvIo& operator=(EvIo&& other) = delete;
		EvIo& operator=(EvIo other) = delete;
		~EvIo();
	};
}

#endif
