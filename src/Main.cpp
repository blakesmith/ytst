#include <stdio.h>

#include "Stream.hpp"

int main(int argc, char **argv) {
	ytst::Stream stream("samples");

	try {
		stream.stream("UDgsfKIL8Sc");
		return 0;
	} catch (...) {
		return -1;
	}
}

