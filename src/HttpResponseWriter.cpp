#include <utility>

#include "Log.hpp"
#include "HttpResponseWriter.hpp"

namespace ytst {
	void HttpResponseWriter::add_callback(std::function<void()> notify) {
		writer.add_callback(notify);
	}

	int HttpResponseWriter::write_response(int code, bool send_length, std::string& body) {
		auto buf = new Buffer(body.c_str(), body.length());
		write_buffer(code, send_length, buf);
		return write_last_chunk();
	}

	int HttpResponseWriter::write_buffer(int code, bool send_length, Buffer* buf) {
		if (!headers_sent) {
			if (send_length) {
				chunked = false;
				header["Content-Length"] = std::to_string(buf->nbytes()+2);
			} else {
				chunked = true;
				header["Transfer-Encoding"] = "chunked";
			}

			write_header(code);
		}

		if (send_length) {
			writer.write_buffer(buf);
		} else {
			write_chunked_buffer(buf);
		}
		
		return 0;
	}

	int HttpResponseWriter::write_buffer(Buffer* buf) {
		return write_buffer(HttpResponse::STATUS_OK, true, buf);
	}

	int HttpResponseWriter::write_last_chunk() {
		if (chunked) {
			return writer.write_buffer(new Buffer("0\r\n\r\n", 5));
		}

		return writer.write_buffer(new Buffer("\r\n", 2));
	}

	int HttpResponseWriter::write_header(int code) {
		std::string code_name;
		int res = HttpResponse::get_name(code, code_name);
		if (res < 0) {
			LOG(logWARNING) << "Invalid HTTP code";

			return res;
		}
		
		std::string headers;
		for (auto& h : header) {
			headers = headers + h.first + ": " + h.second + "\r\n";
		}

		std::string header_response =
			"HTTP/1.1 " + std::to_string(code) + " " + code_name + "\r\n"
			+ headers + "\r\n";

		Buffer* buf = new Buffer(header_response.c_str(), header_response.length());
		writer.write_buffer(buf);
		headers_sent = true;

		LOG(logDEBUG) << "HTTP headers sent";

		return 0;
	}

	std::shared_ptr<Buffer> HttpResponseWriter::get_buffer() {
		return writer.get_buffer();
	}

	bool HttpResponseWriter::has_buffer() {
		return writer.has_buffer();
	}

	int HttpResponseWriter::write_chunked_buffer(Buffer* buf) {
		char lbuf[16];
		if (buf->nbytes() > UINT_MAX) {
			return -1;
		}
		int lsize = snprintf(lbuf, 16, "%x\r\n", static_cast<unsigned int>(buf->nbytes()));
		writer.write_buffer(new Buffer(lbuf, lsize));
		writer.write_buffer(buf);
		writer.write_buffer(new Buffer("\r\n", 2));

		return 0;
	}

	HttpResponseWriter::HttpResponseWriter() {
		headers_sent = false;
	}
}
