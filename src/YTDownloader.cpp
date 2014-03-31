#include <mutex>
#include <vector>
#include <signal.h>
#include <sys/wait.h>

#include "Log.hpp"
#include "YTDownloader.hpp"

namespace ytst {
	YTDownloader::YTDownloader(const std::string& url,
				   const std::string& out,
				   std::shared_ptr<ytst::PythonSupervisor> python_supervisor) :
		url(url),
		out(out),
		python_supervisor(python_supervisor) { }

	YTDownloader::~YTDownloader() {
		if (python_pid > 0) {
			LOG(logDEBUG) << "About to kill child process with pid: " << python_pid;
			kill(python_pid, SIGQUIT);
			wait(nullptr);
		}
	}

	int YTDownloader::download() {
		python_pid = fork();
		if (python_pid == 0) {
			python = python_supervisor->new_python();
			auto module = python->import_module("youtube_dl");

			std::vector<std::string> func_args;
			func_args.push_back("-q");
			func_args.push_back("--no-part");
			func_args.push_back("-o");
			func_args.push_back(out);
			func_args.push_back(url);

			python->call_func(module.get(), "_real_main", func_args);
			exit(0);
		}

		return 0;
	}
}
