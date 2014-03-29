#ifndef YTST_YT_DOWNLOADER_HPP
#define YTST_YT_DOWNLOADER_HPP

#include <string>
#include <memory>

#include "PythonSupervisor.hpp"

namespace ytst {
	class YTDownloader {
		const std::string& url;
		const std::string& out;
		pid_t python_pid;

		std::shared_ptr<ytst::PythonSupervisor> python_supervisor;
		std::shared_ptr<ytst::Python> python;
	public:
		YTDownloader(const std::string& url,
			     const std::string& out,
			     std::shared_ptr<PythonSupervisor> python_supervisor);
		~YTDownloader();
		int download();
	};
}
#endif
