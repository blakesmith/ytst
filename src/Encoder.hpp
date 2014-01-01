#ifndef YTST_ENCODER_HPP
#define YTST_ENCODER_HPP

extern "C" {
#include <libavformat/avformat.h>
}

namespace ytst {
	class Encoder {
	public:
		virtual void open_encoder() = 0;
		virtual int encode_frame(AVFrame* frame) = 0;
	};
}
#endif
