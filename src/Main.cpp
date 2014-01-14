#include <memory>
#include <stdio.h>
#include <signal.h>
#include <execinfo.h>

#include "CmdOpt.hpp"
#include "HttpServer.hpp"

void handler(int sig) {
	void *array[10];
	size_t size;

	// get void*'s for all entries on the stack
	size = backtrace(array, 10);

	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}

int main(int argc, char **argv) {
	signal(SIGSEGV, handler); 

	ytst::CmdOpt opt_parser;
	auto opts = opt_parser.parse_args(argc, argv);
	
	ytst::HttpServer server(&opts);
	server.start();

	return 0;
}

