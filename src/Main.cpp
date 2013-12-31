#include <stdio.h>

#include "Decoder.hpp"
#include "FileEncoder.hpp"

int main(int argc, char **argv) {
	const char* infile = "samples/goose.mp3";
	const char* outfile = "out.sw";

	ytst::Decoder decoder(infile);
	auto decoder_ctxt = decoder.read_file();

	FILE* out = fopen(outfile, "wb");
	ytst::FileEncoder encoder(decoder_ctxt, out);

	AVFrame* frame;
	while ((frame = decoder.decode_frame()) != nullptr) {
		encoder.encode_frame(frame);
	}

	fclose(out);
}
