#ifndef YTST_CMD_OPT_HPP
#define YTST_CMD_OPT_HPP

#include <string>

namespace ytst {
	struct Options {
		std::string fifo_directory;
		std::string python_path;
		int listen_port;
	};

	class CmdOpt {
	public:
		Options parse_args(int argc, char** argv);
	};
}

#endif
