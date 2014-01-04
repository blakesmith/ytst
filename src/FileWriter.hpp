#ifndef YTST_FILE_WRITER_HPP
#define YTST_FILE_WRITTER_HPP

#include <cstdlib>
#include <memory>
#include <functional>

#include "Packet.hpp"

namespace ytst {
	class FileWriter {
		std::unique_ptr<FILE, std::function<void(FILE*)>> file;
	public:
		FileWriter(FILE* out);
		int write_packet(Packet& packet);
	};
}

#endif
