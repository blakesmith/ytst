#ifndef YTST_FILE_WRITER_HPP
#define YTST_FILE_WRITTER_HPP

#include <cstdlib>
#include <memory>
#include <functional>

#include "Writer.hpp"

namespace ytst {
	class FileWriter : public Writer {
		std::unique_ptr<FILE, std::function<void(FILE*)>> file;
	public:
		FileWriter(FILE* out);
		virtual int write_packet(Packet& packet);
	};
}

#endif
