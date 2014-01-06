#include "CmdOpt.hpp"

#include <getopt.h>
#include <cstring>

namespace ytst {
	Options CmdOpt::parse_args(int argc, char** argv) {
		static struct option longopts[] = {
			{ "video-id", required_argument, 0, 'i' },
			{ "fifo-directory", required_argument, 0, 'f' },
			{ 0, 0, 0, 0 }
		};

		Options full_opts;
		full_opts.fifo_directory = "/tmp";

		int ch;
		while ((ch = getopt_long(argc, argv, "f:i:", longopts, NULL)) != -1) {
			switch (ch) {
			case 'i':
				full_opts.video_id = std::string(optarg, strlen(optarg));
				break;
			case 'f':
				full_opts.fifo_directory = std::string(optarg, strlen(optarg));
				break;
			default:
				break;
			}
		}
			
		return full_opts;
	}
}
