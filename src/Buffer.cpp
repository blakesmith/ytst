#include <string.h>

#include "Buffer.hpp"

namespace ytst {
	Buffer::Buffer(const char *bytes, ssize_t nbytes) {
		pos = 0;
		len = nbytes;
		data = new char[nbytes];
		memcpy(data, bytes, nbytes);
	}

	Buffer::~Buffer() {
		delete[] data;
	}

	char *Buffer::dpos() {
		return data + pos;
	}

	ssize_t Buffer::nbytes() {
		return len - pos;
	}
}
