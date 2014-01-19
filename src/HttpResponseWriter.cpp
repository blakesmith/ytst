#include <utility>

#include "Log.hpp"
#include "HttpResponseWriter.hpp"

namespace ytst {
	void HttpResponseWriter::add_callback(std::function<void()> notify) {
		writer.add_callback(notify);
	}

	int HttpResponseWriter::write_response(int code, bool send_length, std::string& body) {
		auto full_body = body+"\r\n";
		auto buf = new Buffer(full_body.c_str(), full_body.length());
		return write_buffer(code, send_length, buf);
	}

	int HttpResponseWriter::write_buffer(int code, bool send_length, Buffer* buf) {
		if (!headers_sent) {
			if (send_length) {
				header["Content-Length"] = std::to_string(buf->nbytes());
			}
			write_header(code);
		}

		writer.write_buffer(buf);
		
		return 0;
	}

	int HttpResponseWriter::write_buffer(Buffer* buf) {
		return write_buffer(HttpResponse::STATUS_OK, false, buf);
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

	Buffer* HttpResponseWriter::get_buffer() {
		return writer.get_buffer();
	}

	bool HttpResponseWriter::has_buffer() {
		return writer.has_buffer();
	}

	HttpResponseWriter::HttpResponseWriter() {
		headers_sent = false;
	}
}
