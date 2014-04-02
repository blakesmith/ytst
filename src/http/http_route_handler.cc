#include "http_route_handler.h"

namespace ytst {
	void HttpRouteHandler::add_route(std::string path, HttpHandler* handle) {
		handles[path] = std::shared_ptr<HttpHandler>(handle);
	}

	void HttpRouteHandler::serve(HttpRequest& request, HttpResponseWriter& writer) {
		auto handle = handles[request.request_path];
		if (handle == nullptr) {
			std::string body = "Route '" + request.request_path + "' not found";
			writer.write_response(HttpResponse::STATUS_NOT_FOUND, false, body);
			return;
		}

		handle->serve(request, writer);
	}
}
