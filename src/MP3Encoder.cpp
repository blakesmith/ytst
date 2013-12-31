#include "MP3Encoder.hpp"
#include "Packet.hpp"

namespace ytst {
	MP3Encoder::MP3Encoder(std::shared_ptr<AVCodecContext> ctxt, FILE* outfile) {
		this->out = outfile;
		this->decoder_context = ctxt;
	}

	void MP3Encoder::open_encoder() {
		const auto codec = avcodec_find_encoder(AV_CODEC_ID_MP2);
		
		if (codec == nullptr) {
			throw std::runtime_error("Could not find a suitable audio encoder");
		}

		encoder_context = std::shared_ptr<AVCodecContext>(avcodec_alloc_context3(codec),
								  [](AVCodecContext* c) {
									  avcodec_close(c);
									  av_free(c);
								  });

		encoder_context.get()->sample_fmt = AV_SAMPLE_FMT_S16;
		encoder_context.get()->bit_rate = 192000;
		encoder_context.get()->sample_rate = select_sample_rate(codec);
		encoder_context.get()->channel_layout = select_channel_layout(codec);
		encoder_context.get()->channels = av_get_channel_layout_nb_channels(encoder_context.get()->channel_layout);

		if (avcodec_open2(encoder_context.get(), codec, nullptr) < 0) {
			throw std::runtime_error("Could not open the codec");
		}
	}

	int MP3Encoder::encode_frame(AVFrame* frame) {
		int has_output, ret;
		ret = avcodec_encode_audio2(encoder_context.get(),
					    &packet.packet,
					    frame,
					    &has_output);

		if (ret < 0) {
			throw std::runtime_error("Error encoding audio frame");
		}

		int written = 0;
		int res;
		res = fwrite(packet.packet.data, 1, packet.packet.size, out);
		if (res > 0) {
			written += res;
		}

		has_output = 1;
		while (has_output != 0) {
			ret = avcodec_encode_audio2(encoder_context.get(),
						    &packet.packet,
						    nullptr,
						    &has_output);
			if (ret < 0) {
				throw std::runtime_error("Error encoding delayed audio frames");
			}
			res = fwrite(packet.packet.data, 1, packet.packet.size, out);
			if (res > 0) {
				written += res;
			}

		}

		return written;
	}

	/* just pick the highest supported samplerate */
	int MP3Encoder::select_sample_rate(AVCodec *codec)
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
	int MP3Encoder::select_channel_layout(AVCodec *codec)
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
