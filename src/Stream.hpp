#ifndef YTST_STREAM_HPP
#define YTST_STREAM_HPP

#include <memory>
#include <string>
#include <cstdio>
#include <stdexcept>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "Writer.hpp"
#include "Python.hpp"

namespace ytst {
	class Stream {
		std::string fifo_directory;
		std::shared_ptr<ytst::Python> python;
		Writer* writer;

		std::string youtube_url(std::string id);
		std::string fifo_location();
		std::string stream_id();

		class Fifo {
			std::string path;
		public:
			Fifo(std::string path) {
				this->path = path;
				if (mkfifo(path.c_str(), 0644) < 0) {
					throw std::runtime_error("Error making named pipe");
				}
			}

			~Fifo() {
				unlink(path.c_str());
			}
		};

	public:
		Stream(std::string fifo_directory,
		       std::shared_ptr<ytst::Python> python,
		       Writer* writer);

		void stream(std::string id);
	};
}
#endif
