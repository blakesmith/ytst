#include <mutex>
#include <vector>

#include "YTDownloader.hpp"

#include "Python.h"

namespace ytst {
	YTDownloader::YTDownloader(std::string url, std::string out) {
		this->url = url;
		this->out = out;

		python.add_path("src/python/youtube-dl");
	}

	int YTDownloader::download() {
		auto module = python.import_module("youtube_dl");

		std::vector<std::string> func_args;
		func_args.push_back("-q");
		func_args.push_back("--no-part");
		func_args.push_back("-o");
		func_args.push_back(out);
		func_args.push_back(url);

		auto result = python.call_func(module.get(), "_real_main", func_args);
		return 0;
	}
}
