#ifndef YTST_BUFFERED_WRITER_HPP
#define YTST_BUFFERED_WRITER_HPP

#include <functional>
#include <queue>
#include <mutex>

#include "Writer.hpp"

using namespace std;

namespace ytst {
	class BufferedWriter : public Writer {
		function<void()> notify_fn;
		queue<Buffer*> buffers;
		mutex queue_mutex;
	public:
		BufferedWriter();
		~BufferedWriter();
		void add_callback(function<void()> notify);
		virtual int write_packet(Packet& packet);
		virtual Buffer* get_buffer();
	};
}
#endif
