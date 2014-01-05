#ifndef YTST_STREAM_HPP
#define YTST_STREAM_HPP

#include <string>

namespace ytst {
	class Stream {
		std::string fifo_directory;

		std::string youtube_url(std::string id);
		std::string fifo_location();
		std::string stream_id();
	public:
		Stream(std::string fifo_directory);
		void stream(std::string id);
	};
}
#endif
