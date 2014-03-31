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
		queue<std::unique_ptr<Buffer>> buffers;
		mutex queue_mutex;
	public:
		BufferedWriter();
		~BufferedWriter();
		void add_callback(function<void()> notify);
		virtual int write_buffer(std::unique_ptr<Buffer> buf);
		virtual std::unique_ptr<Buffer> get_buffer();
		virtual bool has_buffer();
	};
}
#endif
