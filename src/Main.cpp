#include <stdio.h>

#include "YTDownloader.hpp"
#include "Decoder.hpp"
#include "FileWriter.hpp"
#include "MP3Encoder.hpp"
#include "Packet.hpp"

int main(int argc, char **argv) {
	const char* infile = "samples/download.mp4";
	const char* outfile = "download.mp3";

	ytst::YTDownloader downloader("https://www.youtube.com/watch?v=UDgsfKIL8Sc", infile);
	downloader.download();
	
	ytst::Decoder decoder(infile);
	auto decoder_ctxt = decoder.read_file();

	FILE* out = fopen(outfile, "wb");
	ytst::MP3Encoder encoder(decoder_ctxt);
	encoder.open_encoder();

	ytst::FileWriter writer(out);

	AVFrame* frame;
	ytst::Packet packet;
	while ((frame = decoder.decode_frame()) != nullptr) {
		encoder.encode_frame(frame, packet);
		writer.write_packet(packet);
		packet.reset();
	}
}

