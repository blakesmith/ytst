#ifndef YTST_RESPONSE_WRITER_HPP
#define YTST_RESPONSE_WRITER_HPP

#include <map>

#include "BufferedWriter.hpp"
#include "Writer.hpp"
#include "HttpResponseCodes.hpp"

using namespace std;

namespace ytst {
	class HttpResponseWriter : public Writer {
		BufferedWriter writer;
		bool headers_sent;
	public:
		map<string, string> header;

		int write_header(int code);
		virtual int write_packet(Packet& packet);
		virtual Buffer* get_buffer();
	};
}

#endif
