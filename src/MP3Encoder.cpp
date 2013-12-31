#include "MP3Encoder.hpp"
#include "Packet.hpp"

namespace ytst {
	MP3Encoder::MP3Encoder(std::shared_ptr<AVCodecContext> ctxt, FILE* outfile) {
		this->out = outfile;
		this->decoder_context = ctxt;
	}

	void MP3Encoder::open_encoder() {
		const auto codec = avcodec_find_encoder(AV_CODEC_ID_MP3);
		
		if (codec == nullptr) {
			throw std::runtime_error("Could not find a suitable audio encoder");
		}

		encoder_context = std::shared_ptr<AVCodecContext>(avcodec_alloc_context3(codec),
								  [](AVCodecContext* c) {
									  avcodec_close(c);
									  av_free(c);
								  });
		if (avcodec_open2(encoder_context.get(), codec, nullptr) < 0) {
			throw std::runtime_error("Could not open the codec");
		}
	}

	int MP3Encoder::encode_frame(AVFrame* frame) {
		return 0;
	}
}
