#ifndef YTST_HTTP_HANDLER
#define YTST_HTTP_HANDLER

#include "HttpRequest.hpp"
#include "HttpResponseWriter.hpp"

namespace ytst {
	class HttpHandler {
	public:
		virtual void serve(HttpRequest& request, HttpResponseWriter& writer) = 0;
	};
}

#endif
