#ifndef YTST_WRITER_HPP
#define YTST_WRITER_HPP

#include "Packet.hpp"
#include "Buffer.hpp"

namespace ytst {
	class Writer {
	public:
		virtual int write_buffer(Buffer *buf) = 0;
		virtual Buffer* get_buffer() = 0;
		virtual bool has_buffer() = 0;
	};
}
#endif
