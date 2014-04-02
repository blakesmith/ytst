#ifndef YTST_SOCKET_DESC_H
#define YTST_SOCKET_DESC_H

#include <unistd.h>

namespace ytst {
	class SocketDesc {
		int sd;
	public:
		SocketDesc(int sd);
		~SocketDesc();
		int get() const;
	};
}

#endif
