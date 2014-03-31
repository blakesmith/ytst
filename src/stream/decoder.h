#ifndef YTST_DECODER_HPP
#define YTST_DECODER_HPP

#include <string>
#include <memory>

#include "packet.h"

extern "C" {
#include <libavformat/avformat.h>
}

namespace ytst {
	class Decoder {
		const std::string& infile;
		std::shared_ptr<AVFormatContext> avFormat;
		std::shared_ptr<AVCodecContext> avAudioCodec;
		std::shared_ptr<AVFrame> avFrame;

		Packet packet;
		AVStream* audioStream;

	public:
		Decoder(const std::string& infile);
		std::shared_ptr<AVCodecContext> read_file();
		AVFrame* decode_frame();
	};
}

#endif
