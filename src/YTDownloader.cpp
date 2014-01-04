#include <mutex>
#include <cstring>
#include <vector>
#include <string>

#include "YTDownloader.hpp"

#include "Python.h"

namespace ytst {
	YTDownloader::YTDownloader(const char* url, const char* out) {
		this->download_url = url;
		this->file_out = out;

		python.add_path("/Users/blake/src/youtube-dl");
	}

	int YTDownloader::download() {
		auto module = python.import_module("youtube_dl");

		std::vector<std::string> func_args;
		func_args.push_back("--no-part");
		func_args.push_back("-o");
		func_args.push_back(std::string(file_out, strlen(file_out)));
		func_args.push_back(std::string(download_url, strlen(download_url)));

		auto result = python.call_func(module.get(), "_real_main", func_args);
		return 0;
	}
}
