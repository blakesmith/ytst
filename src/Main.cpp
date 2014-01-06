#include <stdio.h>

#include "Stream.hpp"
#include "CmdOpt.hpp"

int main(int argc, char **argv) {
	ytst::CmdOpt opt_parser;
	auto opts = opt_parser.parse_args(argc, argv);

	ytst::Stream stream(opts.fifo_directory);
	stream.stream(opts.video_id);

	return 0;
}

