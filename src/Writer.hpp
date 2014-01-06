#ifndef YTST_WRITER_HPP
#define YTST_WRITER_HPP

#include "Packet.hpp"

namespace ytst {
	class Writer {
	public:
		virtual int write_packet(Packet& packet) = 0;
	};
}
#endif
