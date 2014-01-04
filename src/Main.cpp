#include <stdio.h>

#include "YTDownloader.hpp"
#include "Decoder.hpp"
#include "FileEncoder.hpp"
#include "MP3Encoder.hpp"

int main(int argc, char **argv) {
	const char* infile = "samples/download.mp4";
	const char* outfile = "download.mp3";

	ytst::YTDownloader downloader("https://www.youtube.com/watch?v=UDgsfKIL8Sc", infile);
	downloader.download();
	
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

