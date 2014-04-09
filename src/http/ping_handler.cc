#include "ping_handler.h"

namespace ytst {
	void PingHandler::serve(HttpRequest& request, HttpResponseWriter& writer) {
		std::string pong("pong");
		writer.write_response(HttpResponse::STATUS_OK, false, pong);
	}
}
