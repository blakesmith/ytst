#ifndef YTST_EV_LOOP_H
#define YTST_EV_LOOP_H

#include <ev.h>

namespace ev {
	class Loop {
		struct ev_loop *loop;
	public:
		struct ev_loop* get() const;
		void stop();
		void start();

		Loop();
		~Loop();
		Loop(const Loop& other);
		Loop(Loop&& other);
		Loop& operator=(Loop&& other);
		Loop& operator=(Loop other);
	};
}

#endif
