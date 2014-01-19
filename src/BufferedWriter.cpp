
#include "BufferedWriter.hpp"

namespace ytst {
	BufferedWriter::BufferedWriter() { }
	BufferedWriter::~BufferedWriter() { }

	void BufferedWriter::add_callback(std::function<void()> notify) {
		this->notify_fn = notify;
	}

	int BufferedWriter::write_buffer(Buffer* buf) {
		std::lock_guard<std::mutex> lock(queue_mutex);
		buffers.push(std::shared_ptr<Buffer>(buf));
		notify_fn();

		return buf->len;
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
