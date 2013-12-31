#ifndef YTST_DECODER_HPP
#define YTST_DECODER_HPP

#include <memory>

extern "C" {
#include <libavformat/avformat.h>
}

namespace ytst {
	class Decoder {
		std::shared_ptr<AVFormatContext> avFormat;

		void read_file(const char* infile);
	public:
		Decoder();
		int decode_audio(const char* infile, FILE* out);
	};
}

#endif
