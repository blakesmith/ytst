#include "CmdOpt.hpp"

#include "http/http_server.h"
#include "http/http_route_handler.h"

#include "YoutubeHandler.hpp"
#include "PythonSupervisor.hpp"

int main(int argc, char **argv) {
	ytst::CmdOpt opt_parser;
	auto opts = opt_parser.parse_args(argc, argv);

	auto python_supervisor = make_shared<ytst::PythonSupervisor>();
	python_supervisor->add_default_path(opts.python_path);
	
	ytst::HttpServer server(opts);

	server.set_handler([&opts, python_supervisor] {
			auto handler = new ytst::HttpRouteHandler();

			handler->add_route("/stream", new ytst::YoutubeHandler(opts.fifo_directory, python_supervisor));

			return std::unique_ptr<ytst::HttpHandler>(handler);
		});

	server.start();

	return 0;
}

