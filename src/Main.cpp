#include <stdio.h>

#include "Decoder.hpp"
#include "FileEncoder.hpp"
#include "MP3Encoder.hpp"

int main(int argc, char **argv) {
	const char* infile = "samples/bungle.mp4";
	const char* outfile = "bungle.mp3";
	
	ytst::Decoder decoder(infile);
	auto decoder_ctxt = decoder.read_file();

	FILE* out = fopen(outfile, "wb");
	ytst::MP3Encoder encoder(decoder_ctxt, out);
	encoder.open_encoder();

	AVFrame* frame;
	while ((frame = decoder.decode_frame()) != nullptr) {
		encoder.encode_frame(frame);
	}

	fclose(out);
}

