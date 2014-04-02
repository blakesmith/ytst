#include "socket_desc.h"

namespace ytst {
	SocketDesc::SocketDesc(int sd) : sd(sd) { }
	SocketDesc::~SocketDesc() {
		close(sd);
	}
	
	int SocketDesc::get() const {
		return sd;
	}
}
