#include "CmdOpt.hpp"

#include <getopt.h>
#include <cstring>

namespace ytst {
	Options CmdOpt::parse_args(int argc, char** argv) {
		static struct option longopts[] = {
			{ "listen-port", optional_argument, 0, 'P' },
			{ "fifo-directory", required_argument, 0, 'f' },
			{ "python-path", required_argument, 0, 'p' },
			{ 0, 0, 0, 0 }
		};

		Options full_opts;
		full_opts.fifo_directory = "/tmp";
		full_opts.python_path = "/usr/local/lib/ytst/python/youtube-dl";
		full_opts.listen_port = 8192;

		int ch;
		while ((ch = getopt_long(argc, argv, "f:P:p:", longopts, NULL)) != -1) {
			switch (ch) {
			case 'P':
				full_opts.listen_port = atoi(optarg);
				break;
			case 'f':
				full_opts.fifo_directory = std::string(optarg, strlen(optarg));
				break;
			case 'p':
				full_opts.python_path = std::string(optarg, strlen(optarg));
				break;
			default:
				break;
			}
		}
			
		return full_opts;
	}
}
