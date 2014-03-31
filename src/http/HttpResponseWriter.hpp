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
		bool chunked;

		Buffer* make_chunk(Buffer* buf);
	public:
		map<string, string> header;

		void add_callback(std::function<void()> notify);
		int write_header(int code, bool chunked, ssize_t len);
		int write_response(int code, bool chunked, std::string& body);
		int write_buffer(int code, bool send_length, std::unique_ptr<Buffer> buf);
		int write_chunked_buffer(std::unique_ptr<Buffer> buf);
		int write_last_chunk();
		virtual int write_buffer(std::unique_ptr<Buffer> buf);
		virtual std::unique_ptr<Buffer> get_buffer();
		virtual bool has_buffer();

		HttpResponseWriter();
	};
}

#endif
