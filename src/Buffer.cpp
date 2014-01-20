#include <string.h>

#include "Buffer.hpp"

namespace ytst {
	Buffer::Buffer(const char *bytes, ssize_t nbytes) {
		pos = 0;
		len = nbytes;
		data = std::unique_ptr<char>(new char[nbytes]);
		memcpy(data.get(), bytes, nbytes);
	}

	Buffer::~Buffer() {
	}

	char *Buffer::dpos() {
		return data.get() + pos;
	}

	ssize_t Buffer::nbytes() {
		return len - pos;
	}
}
