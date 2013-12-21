#include <stdlib.h>
#include <iostream>

int main(int argc, char **argv) {
	int port = 8192;
	if (argc > 1) {
		port = atoi(argv[1]);
	}

	std::cout << port;

	return 0;
}
