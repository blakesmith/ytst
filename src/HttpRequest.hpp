#ifndef YTST_HTTP_REQUEST
#define YTST_HTTP_REQUEST

#include <string>
#include <map>

namespace ytst {
	struct HttpRequest {
		std::map<std::string, std::string> headers;
		std::string request_method;
		std::string request_uri;
		std::string fragment;
		std::string request_path;
		std::string query_string;
		std::string http_version;
		const char *body;
		int body_length;
	};
}

#endif
