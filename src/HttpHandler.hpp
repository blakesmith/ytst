#ifndef YTST_HTTP_HANDLER
#define YTST_HTTP_HANDLER

#include <map>

#include "HttpRequest.hpp"
#include "HttpResponseWriter.hpp"

namespace ytst {
	class HttpHandler {
	public:
		virtual void serve(HttpRequest& request, HttpResponseWriter& writer) = 0;
	protected:
		int parse_query(std::map<std::string, std::string>& res, std::string& q);

	};
}

#endif
