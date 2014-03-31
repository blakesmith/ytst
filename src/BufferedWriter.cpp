#include "BufferedWriter.hpp"

namespace ytst {
	BufferedWriter::BufferedWriter() { }
	BufferedWriter::~BufferedWriter() { }

	void BufferedWriter::add_callback(std::function<void()> notify) {
		notify_fn = notify;
	}

	int BufferedWriter::write_buffer(std::unique_ptr<Buffer> buf) {
		ssize_t len = buf->len;
		std::lock_guard<std::mutex> lock(queue_mutex);
		buffers.push(std::move(buf));
		notify_fn();

		return len;
	}

	std::unique_ptr<Buffer> BufferedWriter::get_buffer() {
		std::lock_guard<std::mutex> lock(queue_mutex);
		auto buf = std::move(buffers.front());
		buffers.pop();
		return std::move(buf);
	}

	bool BufferedWriter::has_buffer() {
		std::lock_guard<std::mutex> lock(queue_mutex);
		return !buffers.empty();
	}
}
