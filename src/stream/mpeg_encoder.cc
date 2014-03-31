#include <iostream>

#include "Log.hpp"
#include "mpeg_encoder.h"

namespace ytst {
	MPEGEncoder::MPEGEncoder(std::shared_ptr<AVCodecContext> ctxt) : decoder_context(ctxt) { }

	void MPEGEncoder::open_encoder() {
#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(55, 28, 1)
		const auto codec = avcodec_find_encoder(AV_CODEC_ID_MP3);
#else
		const auto codec = avcodec_find_encoder(CODEC_ID_MP3);
#endif
		
		if (codec == nullptr) {
			LOG(logWARNING) << "Could not find audio codec!";
			throw std::runtime_error("Could not find a suitable audio encoder");
		}

		encoder_context = std::shared_ptr<AVCodecContext>(avcodec_alloc_context3(codec),
								  [](AVCodecContext* c) {
									  avcodec_close(c);
									  av_free(c);
								  });

		encoder_context->sample_fmt = decoder_context->sample_fmt;
		encoder_context->bit_rate = 128000;
		encoder_context->sample_rate = 44100;
		encoder_context->channel_layout = select_channel_layout(codec);
		encoder_context->channels = av_get_channel_layout_nb_channels(encoder_context->channel_layout);

		if (avcodec_open2(encoder_context.get(), codec, nullptr) < 0) {
			throw std::runtime_error("Could not open the codec");
		}

		LOG(logINFO) << "Encoder frame size: " << encoder_context->frame_size;
	}

	int MPEGEncoder::encode_frame(AVFrame* frame, Packet& packet) {
		int has_output, ret;
		ret = avcodec_encode_audio2(encoder_context.get(),
					    &packet.packet,
					    frame,
					    &has_output);

		if (ret < 0) {
			char errbuff[256];
			av_strerror(ret, errbuff, 256);
			throw std::runtime_error(errbuff);
		}

		return ret;
	}

	/* just pick the highest supported samplerate */
	int MPEGEncoder::select_sample_rate(AVCodec *codec)
	{
		const int *p;
		int best_samplerate = 0;

		if (!codec->supported_samplerates)
			return 44100;

		p = codec->supported_samplerates;
		while (*p) {
			best_samplerate = FFMAX(*p, best_samplerate);
			p++;
		}
		return best_samplerate;
	}

        /* select layout with the highest channel count */
	int MPEGEncoder::select_channel_layout(AVCodec *codec)
	{
		const uint64_t *p;
		uint64_t best_ch_layout = 0;
		int best_nb_channels   = 0;

		if (!codec->channel_layouts)
			return AV_CH_LAYOUT_STEREO;

		p = codec->channel_layouts;
		while (*p) {
			int nb_channels = av_get_channel_layout_nb_channels(*p);

			if (nb_channels > best_nb_channels) {
				best_ch_layout    = *p;
				best_nb_channels = nb_channels;
			}
			p++;
		}
		return best_ch_layout;
	}
}
