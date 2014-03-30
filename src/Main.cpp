#include "CmdOpt.hpp"
#include "HttpServer.hpp"

int main(int argc, char **argv) {
	ytst::CmdOpt opt_parser;
	auto opts = opt_parser.parse_args(argc, argv);
	
	ytst::HttpServer server(opts);
	server.start();

	return 0;
}

