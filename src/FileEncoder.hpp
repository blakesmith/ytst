#ifndef YTST_FILE_ENCODER_HPP
#define YTST_FILE_ENCODER_HPP

#include <memory>

extern "C" {
#include <libavformat/avformat.h>
}

namespace ytst {
	class FileEncoder {
		FILE* out;
		std::shared_ptr<AVCodecContext> context;
	public:
		FileEncoder(std::shared_ptr<AVCodecContext> ctxt, FILE* outfile);
		int encode_frame(AVFrame* frame);
	};
}
#endif
