#ifndef YTST_MP3_ENCODER_HPP
#define YTST_MP3_ENCODER_HPP

#include <memory>

#include "Encoder.hpp"
#include "Packet.hpp"

extern "C" {
#include <libavformat/avformat.h>
}

namespace ytst {
// This with FileEncoder should extend from an Encoder abstract class
	class MP3Encoder : Encoder {
		FILE* out;
		std::shared_ptr<AVCodecContext> decoder_context;
		std::shared_ptr<AVCodecContext> encoder_context;
		Packet packet;

		int select_sample_rate(AVCodec* codec);
		int select_channel_layout(AVCodec* codec);
	public:
		MP3Encoder(std::shared_ptr<AVCodecContext> ctxt, FILE* outfile);
		void open_encoder();
		int encode_frame(AVFrame* frame);
	};
}
#endif
