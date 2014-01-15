#include <utility>

#include "HttpResponseWriter.hpp"

namespace ytst {
	int HttpResponseWriter::write_packet(Packet& packet) {
		if (!headers_sent) {
			write_header(HttpResponse::STATUS_OK);
		}
		return 0;
	}

	int HttpResponseWriter::write_header(int code) {
		return 0;
	}

	Buffer* HttpResponseWriter::get_buffer() {
		return writer.get_buffer();
	}
}
