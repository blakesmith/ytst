#ifndef YTST_BUFFERED_WRITER_HPP
#define YTST_BUFFERED_WRITER_HPP

#include <functional>
#include <queue>
#include <mutex>

#include "Writer.hpp"

namespace ytst {
	class BufferedWriter : public Writer {
		std::function<void()> notify_fn;
		std::queue<Buffer*> buffers;
		std::mutex queue_mutex;
	public:
		BufferedWriter();
		void add_callback(std::function<void()> notify);
		virtual int write_packet(Packet& packet);
		virtual Buffer* get_buffer();
	};
}
#endif
