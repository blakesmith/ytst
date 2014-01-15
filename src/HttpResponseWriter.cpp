#include <utility>

#include "HttpResponseWriter.hpp"

namespace ytst {
	int HttpResponseWriter::write_packet(Packet& packet) {
		return 0;
	}

	Buffer* HttpResponseWriter::get_buffer() {
		return writer.get_buffer();
	}
}
