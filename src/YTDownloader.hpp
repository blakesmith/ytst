#ifndef YTST_YT_DOWNLOADER_HPP
#define YTST_YT_DOWNLOADER_HPP

#include <string>
#include <memory>

#include "Python.hpp"

namespace ytst {
	class YTDownloader {
		std::string url;
		std::string out;
		pid_t python_pid;

		std::shared_ptr<ytst::Python> python;
	public:
		YTDownloader(std::string url,
			     std::string out,
			     std::shared_ptr<Python> python);
		~YTDownloader();
		int download();
	};
}
#endif
