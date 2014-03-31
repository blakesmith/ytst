#ifndef YTST_STREAM_HPP
#define YTST_STREAM_HPP

#include <memory>
#include <string>
#include <cstdio>
#include <stdexcept>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <atomic>

#include "http/http_response_writer.h"
#include "python/python_supervisor.h"

namespace ytst {
	class Stream {
		const std::string& fifo_directory;
		std::shared_ptr<PythonSupervisor> python_supervisor;
		std::atomic<bool>& stream_running;
		HttpResponseWriter& writer;

		std::string youtube_url(const std::string& id);
		std::string fifo_location();
		std::string stream_id();

		class Fifo {
			const std::string& path;
		public:
			Fifo(const std::string& path) : path(path) {
				if (mkfifo(path.c_str(), 0644) < 0) {
					throw std::runtime_error("Error making named pipe");
				}
			}

			~Fifo() {
				unlink(path.c_str());
			}
		};

	public:
		Stream(const std::string& fifo_directory,
		       std::shared_ptr<PythonSupervisor> python_supervisor,
		       std::atomic<bool>& stream_running,
		       HttpResponseWriter& writer);
		~Stream();

		void stream(const std::string& id);
	};
}
#endif
