#ifndef YTST_HTTP_HANDLER
#define YTST_HTTP_HANDLER

#include <map>

#include "http_request.h"
#include "http_response_writer.h"

namespace ytst {
	class HttpHandler {
	public:
		virtual void serve(HttpRequest& request, HttpResponseWriter& writer) = 0;
	protected:
		std::map<std::string, std::string>  parse_query(std::string& q);

	};
}

#endif
