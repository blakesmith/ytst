#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <memory>

#include "Decoder.hpp"

namespace ytst {
	Decoder::Decoder(const char* infile) {
		static std::once_flag initFlag;
		std::call_once(initFlag, []() { av_register_all(); });
		this->infile = infile;
		audioStream = nullptr;
	}

	std::shared_ptr<AVCodecContext> Decoder::read_file() {
		avFormat = std::shared_ptr<AVFormatContext>(avformat_alloc_context(), &avformat_free_context);
		auto avFormatPtr = avFormat.get();

		if (avformat_open_input(&avFormatPtr, infile, nullptr, nullptr) != 0) {
			throw std::runtime_error("Error opening the file");
		}

		if (avformat_find_stream_info(avFormat.get(), nullptr) < 0) {
			throw std::runtime_error("Error finding stream info");
		}

		std::cout << "Codec ids found: " << std::endl;
		for (unsigned int i = 0; i < avFormatPtr->nb_streams; ++i) {
			auto stream = avFormatPtr->streams[i];
			auto codecId = stream->codec->codec_id;
			std::cout << codecId << std::endl;
		}

		for (unsigned int i = 0; i < avFormatPtr->nb_streams; ++i) {
			if (avFormatPtr->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
				audioStream = avFormatPtr->streams[i];
				break;
			}
		}

		if (!audioStream) {
			throw std::runtime_error("Didn't find any audio stream");
		}

		const auto codec = avcodec_find_decoder(audioStream->codec->codec_id);
		if (codec == nullptr) {
			throw std::runtime_error("Could not find a suitable audio decoder");
		}

		avAudioCodec = std::shared_ptr<AVCodecContext>(avcodec_alloc_context3(codec),
							       [](AVCodecContext* c) {
								       avcodec_close(c);
								       av_free(c);
							       });

		if (avcodec_open2(avAudioCodec.get(), codec, nullptr) < 0) {
			throw std::runtime_error("Could not open the codec");
		}

		int planar = av_sample_fmt_is_planar(avAudioCodec->sample_fmt);
		std::cout << "Planar: " << planar << std::endl;
		std::cout << "Sample fmt: " << avAudioCodec->sample_fmt << std::endl;

		avFrame = std::shared_ptr<AVFrame>(av_frame_alloc(), [](AVFrame* fr) { av_frame_free(&fr); });

		return avAudioCodec;
	}

	AVFrame* Decoder::decode_frame() {
		auto avFormatPtr = avFormat.get();

		while (true) {
			int readFrame = av_read_frame(avFormatPtr, &packet.packet);
			if (readFrame < 0) {
				return nullptr;
			}
		
			if (packet.packet.stream_index != audioStream->index) {
				continue;
			} else {
				break;
			}
		}

		int isFrameAvailable = 0;
		const auto processedLength = avcodec_decode_audio4(avAudioCodec.get(),
								   avFrame.get(),
								   &isFrameAvailable,
								   &packet.packet);
		if (processedLength < 0) {
			throw std::runtime_error("Error while processing data");
		}

		if (isFrameAvailable) {
			return avFrame.get();
		}

		// Should never reach here
		return nullptr;
	}
}