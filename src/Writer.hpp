#ifndef YTST_WRITER_HPP
#define YTST_WRITER_HPP

#include <memory>

#include "Packet.hpp"
#include "Buffer.hpp"

namespace ytst {
	class Writer {
	public:
		virtual int write_buffer(std::unique_ptr<Buffer> buf) = 0;
		virtual std::unique_ptr<Buffer> get_buffer() = 0;
		virtual bool has_buffer() = 0;
	};
}
#endif
