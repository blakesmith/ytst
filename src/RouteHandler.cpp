#include "RouteHandler.hpp"

namespace ytst {
	void RouteHandler::add_route(std::string path, HttpHandler* handle) {
		handles[path] = std::unique_ptr<HttpHandler>(handle);
	}

	std::unique_ptr<HttpHandler> RouteHandler::get_route(std::string path) {
		return std::move(handles[path]);
	}

	void RouteHandler::serve(HttpRequest& request, HttpResponseWriter& writer) {
		auto handle = std::move(handles[request.request_path]);
		if (handle == nullptr) {
			std::string body = "Route '" + request.request_path + "' not found";
			writer.write_response(HttpResponse::STATUS_NOT_FOUND, false, body);
			return;
		}

		handle->serve(request, writer);
	}
}
