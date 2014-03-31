#ifndef YTST_HTTP_PARSER_HPP
#define YTST_HTTP_PARSER_HPP

#include <map>
#include <string>

extern "C" {
#include "http11_parser.h"
}

#include "HttpRequest.hpp"

using namespace std;

namespace ytst {
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
		int execute(HttpRequest *req, char *data, int len, int offset);
		int nread();
		bool finish();
		bool is_finished();
		bool has_error();
		void reset();
		static int parse_query(map<string, string>& res, string& q);

		HttpParser();
		~HttpParser();
	};
}

#endif
