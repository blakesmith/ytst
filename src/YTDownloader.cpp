#include <mutex>
#include <vector>
#include <signal.h>

#include "Log.hpp"
#include "YTDownloader.hpp"
#include "Python.hpp"

namespace ytst {
	YTDownloader::YTDownloader(std::string url,
				   std::string out,
				   std::shared_ptr<ytst::Python> python) {
		this->url = url;
		this->out = out;
		this->python = python;
	}

	YTDownloader::~YTDownloader() {
		if (python_pid > 0) {
			LOG(logDEBUG) << "About to kill child process with pid: " << python_pid;
			kill(python_pid, SIGQUIT);
			wait(nullptr);
		}
	}

	int YTDownloader::download() {
		auto module = python->import_module("youtube_dl");

		std::vector<std::string> func_args;
		func_args.push_back("-q");
		func_args.push_back("--no-part");
		func_args.push_back("-o");
		func_args.push_back(out);
		func_args.push_back(url);

		python_pid = python->call_async(module.get(), "_real_main", func_args);
		return 0;
	}
}
