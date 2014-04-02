#ifndef YTST_BUFFERED_WRITER_HPP
#define YTST_BUFFERED_WRITER_HPP

#include <functional>
#include <queue>
#include <list>
#include <mutex>

#include "writer.h"

namespace ytst {
	class BufferedWriter : public Writer {
		std::function<void()> notify_fn;
		std::queue<std::shared_ptr<Buffer>, std::list<std::shared_ptr<Buffer> > > buffers;
		std::mutex queue_mutex;
	public:
		BufferedWriter();
		~BufferedWriter();
		void add_callback(std::function<void()> notify);
		virtual int write_buffer(std::shared_ptr<Buffer> buf);
		virtual std::shared_ptr<Buffer> get_buffer();
		virtual bool has_buffer();
	};
}
#endif
