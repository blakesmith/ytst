#include <string.h>

#include "buffer.h"

namespace ytst {
	Buffer::Buffer(const char *bytes, ssize_t nbytes) :
		data(new char[nbytes])
	{
		pos = 0;
		len = nbytes;
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
