#include <stdio.h>

#include "FileEncoder.hpp"
#include "Packet.hpp"

namespace ytst {
	FileEncoder::FileEncoder(std::shared_ptr<AVCodecContext> ctxt, FILE* outfile) {
		this->out = outfile;
		this->decoder_context = ctxt;
	}

	int FileEncoder::encode_frame(AVFrame* frame) {
		int plane_size;
		int planar = av_sample_fmt_is_planar(decoder_context->sample_fmt);
		int frame_size = av_samples_get_buffer_size(&plane_size,
							    decoder_context.get()->channels,
							    frame->nb_samples,
							    decoder_context.get()->sample_fmt,
							    1);


		int written = 0;
		int res;
		if (planar) {
			for (int ch = 0; ch < decoder_context.get()->channels; ch++) {
				res = fwrite(frame->extended_data[ch], 1, frame->linesize[ch], out);
				if (res > 0) {
					written += res;
				}
			}
		} else {
			res = fwrite(frame->extended_data[0], 1, frame_size, out);
			if (res > 0) {
				written += res;
			}
		}

		return written;
	}
}
