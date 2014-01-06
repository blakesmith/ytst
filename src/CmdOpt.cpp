#include "CmdOpt.hpp"

#include <getopt.h>
#include <cstring>

namespace ytst {
	static struct option longopts[] = {
		{ "video-id", required_argument, 0, 'i' },
		{ 0, 0, 0, 0 }
	};

	Options CmdOpt::parse_args(int argc, char** argv) {
		Options full_opts;
		int ch;

		while ((ch = getopt_long(argc, argv, "i:", longopts, NULL)) != -1) {
			switch (ch) {
			case 'i':
				full_opts.video_id = std::string(optarg, strlen(optarg));
				break;
			default:
				break;
			}
		}
			
		return full_opts;
	}
}
