#ifndef YTST_YT_DOWNLOADER_HPP
#define YTST_YT_DOWNLOADER_HPP

#include "Python.hpp"

namespace ytst {
	class YTDownloader {
		const char* download_url;
		const char* file_out;

		Python python;
	public:
		YTDownloader(const char* url, const char* out);
		int download();
	};
}
#endif
