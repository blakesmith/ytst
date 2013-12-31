#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <memory>

#include "Decoder.hpp"

int main(int argc, char **argv) {
	const char* infile = "samples/goose.mp3";
	const char* outfile = "out.sw";

	ytst::Decoder decoder;

	FILE* out = fopen(outfile, "wb");
	decoder.decode_audio(infile, out);
	fclose(out);
}
