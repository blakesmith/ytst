#ifndef YTST_YT_DOWNLOADER_HPP
#define YTST_YT_DOWNLOADER_HPP

#include <string>

#include "Python.hpp"

namespace ytst {
	class YTDownloader {
		std::string url;
		std::string out;

		Python python;
	public:
		YTDownloader(std::string url, std::string out);
		int download();
	};
}
#endif
