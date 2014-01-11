#include "HttpParser.hpp"

#define MAX_FIELD_NAME_LENGTH 256
#define MAX_FIELD_VALUE_LENGTH (80 * 1024)
#define MAX_REQUEST_URI_LENGTH (1024 * 12)
#define MAX_FRAGMENT_LENGTH 1024
#define MAX_REQUEST_PATH_LENGTH 1024
#define MAX_QUERY_STRING_LENGTH (1024 * 10)
#define MAX_HEADER_LENGTH (1024 * (80 + 32))

#define VALIDATE_MAX_LENGTH(len, N) if(len > MAX_##N##_LENGTH) { throw std::runtime_error("Invalid request element length"); }

namespace ytst {
	void HttpParser::http_field(void *data, const char *field, size_t flen, const char *value, size_t vlen) {
		HttpParser *parser = reinterpret_cast<HttpParser*>(data);

		VALIDATE_MAX_LENGTH(flen, FIELD_NAME);
		VALIDATE_MAX_LENGTH(vlen, FIELD_VALUE);

		string f = string(field, flen);
		string v = string(value, vlen);

		parser->req->headers[f] = v;
	}

	void HttpParser::request_method(void *data, const char *at, size_t length) {
		HttpParser *parser = reinterpret_cast<HttpParser*>(data);

		string val = string(at, length);
		parser->req->request_method = val;
	}

	void HttpParser::request_uri(void *data, const char *at, size_t length) {
		HttpParser *parser = reinterpret_cast<HttpParser*>(data);

		VALIDATE_MAX_LENGTH(length, REQUEST_URI);

		string val = string(at, length);
		parser->req->request_uri = val;
	}

	void HttpParser::fragment(void *data, const char *at, size_t length) {
		HttpParser *parser = reinterpret_cast<HttpParser*>(data);

		VALIDATE_MAX_LENGTH(length, FRAGMENT);

		string val = string(at, length);
		parser->req->fragment = val;
	}

	void HttpParser::request_path(void *data, const char *at, size_t length) {
		HttpParser *parser = reinterpret_cast<HttpParser*>(data);

		VALIDATE_MAX_LENGTH(length, REQUEST_PATH);

		string val = string(at, length);
		parser->req->request_path = val;
	}

	void HttpParser::query_string(void *data, const char *at, size_t length) {
		HttpParser *parser = reinterpret_cast<HttpParser*>(data);

		VALIDATE_MAX_LENGTH(length, QUERY_STRING);

		string val = string(at, length);
		parser->req->query_string = val;
	}

	void HttpParser::http_version(void *data, const char *at, size_t length) {
		HttpParser *parser = reinterpret_cast<HttpParser*>(data);
		string val = string(at, length);
		parser->req->http_version = val;
	}

	void HttpParser::header_done(void *data, const char *at, size_t length) {
		HttpParser *parser = reinterpret_cast<HttpParser*>(data);
		parser->req->body = at;
		parser->req->body_length = length;
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
