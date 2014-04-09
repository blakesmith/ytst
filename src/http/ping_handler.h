#ifndef YTST_PING_HANDLER_H
#define YTST_PING_HANDLER_H

#include "http_handler.h"

namespace ytst {
	class PingHandler : public HttpHandler {
		virtual void serve(HttpRequest& request, HttpResponseWriter& writer);
	};
}

#endif
