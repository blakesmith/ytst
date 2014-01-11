#ifndef HTTP_PARSER_HPP
#define HTTP_PARSER_HPP

#include <map>
#include <string>

extern "C" {
#include "http11_parser.h"
}

using namespace std;

namespace ytst {
	struct HttpRequest {
		map<string, string> headers;
		string request_method;
		string request_uri;
		string fragment;
		string request_path;
		string query_string;
		string http_version;
		const char *body;
		int body_length;
	};

	class HttpParser {
		http_parser hp;
		HttpRequest *req;
		
		static void http_field(void *data, const char *field, size_t flen, const char *value, size_t vlen);
		static void request_method(void *data, const char *at, size_t length);
		static void request_uri(void *data, const char *at, size_t length);
		static void fragment(void *data, const char *at, size_t length);
		static void request_path(void *data, const char *at, size_t length);
		static void query_string(void *data, const char *at, size_t length);
		static void http_version(void *data, const char *at, size_t length);
		static void header_done(void *data, const char *at, size_t length);
	public:
		int execute(char *data, int offset);
		int nread();
		bool finish();
		bool is_finished();
		bool has_error();
		void reset();

		HttpParser(HttpRequest *req);
		~HttpParser();
	};
}

#endif
