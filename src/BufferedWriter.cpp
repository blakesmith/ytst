#include "BufferedWriter.hpp"

namespace ytst {
	BufferedWriter::BufferedWriter() { }

	void BufferedWriter::add_callback(std::function<void()> notify) {
		this->notify_fn = notify;
	}

	int BufferedWriter::write_packet(Packet& packet) {
		Buffer* buf = new Buffer((const char *)packet.packet.data, packet.packet.size);
		queue_mutex.lock();
		buffers.push(buf);
		queue_mutex.unlock();
		notify_fn();

		return buf->len;
	}

	Buffer* BufferedWriter::get_buffer() {
		queue_mutex.lock();
		Buffer* buf = buffers.front();
		buffers.pop();
		queue_mutex.unlock();

		return buf;
	}
}
