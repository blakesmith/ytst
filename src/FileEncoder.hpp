#ifndef YTST_FILE_ENCODER_HPP
#define YTST_FILE_ENCODER_HPP

#include <memory>

#include "Encoder.hpp"

extern "C" {
#include <libavformat/avformat.h>
}

namespace ytst {
	class FileEncoder : Encoder {
		FILE* out;
		std::shared_ptr<AVCodecContext> decoder_context;
	public:
		FileEncoder(std::shared_ptr<AVCodecContext> decoder_ctxt, FILE* outfile);
		void open_encoder();
		int encode_frame(AVFrame* frame);
	};
}
#endif
