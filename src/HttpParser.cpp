#include "HttpParser.hpp"

namespace ytst {
	void HttpParser::http_field(void *data, const char *field, size_t flen, const char *value, size_t vlen) {
	}

	void HttpParser::request_method(void *data, const char *at, size_t length) {
	}

	void HttpParser::request_uri(void *data, const char *at, size_t length) {
	}

	void HttpParser::fragment(void *data, const char *at, size_t length) {
	}

	void HttpParser::request_path(void *data, const char *at, size_t length) {
	}

	void HttpParser::query_string(void *data, const char *at, size_t length) {
	}

	void HttpParser::http_version(void *data, const char *at, size_t length) {
	}

	void HttpParser::header_done(void *data, const char *at, size_t length) {
	}

	HttpParser::HttpParser(HttpRequest *req) : req(req) {
		hp.http_field = http_field;
		hp.request_method = request_method;
		hp.request_uri = request_uri;
		hp.fragment = fragment;
		hp.request_path = request_path;
		hp.query_string = query_string;
		hp.http_version = http_version;
		hp.header_done = header_done;
		http_parser_init(&hp);
		hp.data = reinterpret_cast<void*>(this);
	}

	HttpParser::~HttpParser() {
	}

	int HttpParser::execute(char *data, int offset) {
		return 0;
	}

	int HttpParser::nread() {
		return 0;
	}
	
	bool HttpParser::finish() {
		return true;
	}

	bool HttpParser::is_finished() {
		return false;
	}

	void HttpParser::reset() {
	}
}
