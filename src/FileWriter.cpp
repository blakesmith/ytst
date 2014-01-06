#include "FileWriter.hpp"

namespace ytst {
	FileWriter::FileWriter(FILE* out) {
		file = std::unique_ptr<FILE, std::function<void(FILE*)>>(out, fclose);
	}

	int FileWriter::write_packet(Packet& packet) {
		int res = fwrite(packet.packet.data, 1, packet.packet.size, file.get());
		if (res < 0) {
			throw std::runtime_error("Error writing audio packet");
		}

		return res;
	}

	Buffer* FileWriter::get_buffer() {
		return nullptr;
	}
}
