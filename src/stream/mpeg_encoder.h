#ifndef YTST_MP3_ENCODER_HPP
#define YTST_MP3_ENCODER_HPP

#include <memory>
#include <stdexcept>

#include "encoder.h"
#include "packet.h"

extern "C" {
#include <libavformat/avformat.h>
}

namespace ytst {
	class MPEGEncoder : Encoder {
		std::shared_ptr<AVCodecContext> decoder_context;
		std::shared_ptr<AVCodecContext> encoder_context;

		int select_sample_rate(AVCodec* codec);
		int select_channel_layout(AVCodec* codec);
	public:
		MPEGEncoder(std::shared_ptr<AVCodecContext> ctxt);
		void open_encoder();
		int encode_frame(AVFrame* frame, Packet& packet);
	};
}
#endif
