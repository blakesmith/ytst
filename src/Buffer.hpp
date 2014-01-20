#ifndef YTST_BUFFER_HPP
#define YTST_BUFFER_HPP

#include <memory>

#include <stdlib.h>
#include <resolv.h>

namespace ytst {
	struct Buffer {
		std::unique_ptr<char> data;
		ssize_t len;
		ssize_t pos;

		Buffer(const char *bytes, ssize_t nbytes);
		virtual ~Buffer();

		char *dpos();
		ssize_t nbytes();
	};
}
#endif
