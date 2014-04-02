#include "buffered_writer.h"

namespace ytst {
	BufferedWriter::BufferedWriter() { }
	BufferedWriter::~BufferedWriter() { }

	void BufferedWriter::add_callback(std::function<void()> notify) {
		notify_fn = notify;
	}

	int BufferedWriter::write_buffer(std::shared_ptr<Buffer> buf) {
		std::lock_guard<std::mutex> lock(queue_mutex);
		ssize_t len = buf->len;
		buffers.push(buf);
		notify_fn();

		return len;
	}

	std::shared_ptr<Buffer> BufferedWriter::get_buffer() {
		std::lock_guard<std::mutex> lock(queue_mutex);
		auto buf = buffers.front();
		buffers.pop();
		return buf;
	}

	bool BufferedWriter::has_buffer() {
		std::lock_guard<std::mutex> lock(queue_mutex);
		return !buffers.empty();
	}
}
