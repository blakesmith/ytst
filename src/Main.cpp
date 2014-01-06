#include <memory>
#include <stdio.h>

#include "Stream.hpp"
#include "CmdOpt.hpp"
#include "Python.hpp"

int main(int argc, char **argv) {
	ytst::CmdOpt opt_parser;
	auto opts = opt_parser.parse_args(argc, argv);

	ytst::Python* py = new ytst::Python;
	std::shared_ptr<ytst::Python> python(py);
	python.get()->add_path(opts.python_path.c_str());

	ytst::Stream stream(opts.fifo_directory, python);
	stream.stream(opts.video_id);

	return 0;
}

