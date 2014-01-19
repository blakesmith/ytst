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

		void add_callback(std::function<void()> notify);
		int write_header(int code);
		int write_response(int code, bool send_length, std::string& body);
		int write_buffer(int code, bool send_length, Buffer* buf);
		virtual int write_buffer(Buffer* buf);
		virtual std::shared_ptr<Buffer> get_buffer();
		virtual bool has_buffer();

		HttpResponseWriter();
	};
}

#endif
