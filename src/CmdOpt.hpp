#ifndef YTST_CMD_OPT_HPP
#define YTST_CMD_OPT_HPP

#include <string>

namespace ytst {
	struct Options {
		std::string video_id;
		std::string fifo_directory;
	};

	class CmdOpt {
	public:
		Options parse_args(int argc, char** argv);
	};
}

#endif
