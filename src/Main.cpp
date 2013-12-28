#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <memory>
#include <vector>

extern "C" {
#include <libavformat/avformat.h>
}

#include "Packet.hpp"

static void init() {
	static std::once_flag initFlag;

	std::call_once(initFlag, []() { av_register_all(); });
}

static int decode_audio(std::shared_ptr<AVFormatContext> avFormatPtr, FILE* out) {
	auto avFormat = avFormatPtr.get();
	std::cout << "Codec ids found: " << std::endl;
	for (unsigned int i = 0; i < avFormat->nb_streams; ++i) {
		auto stream = avFormat->streams[i];
//		auto codecType = stream->codec->codec_type;
		auto codecId = stream->codec->codec_id;
		std::cout << codecId << std::endl;
	}

	AVStream *audioStream = nullptr;
	for (unsigned int i = 0; i < avFormat->nb_streams; ++i) {
		if (avFormat->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
			audioStream = avFormat->streams[i];
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

	std::shared_ptr<AVCodecContext> avAudioCodec(avcodec_alloc_context3(codec),
						     [](AVCodecContext* c) {
							     avcodec_close(c);
							     av_free(c);
						     });

	if (avcodec_open2(avAudioCodec.get(), codec, nullptr) < 0) {
		throw std::runtime_error("Could not open the codec");
	}

	std::shared_ptr<AVFrame> avFrame(av_frame_alloc(), [](AVFrame* fr) { av_frame_free(&fr); });
	ytst::Packet packet;
	int offsetInData = 0;

	if (!out) {
		throw std::runtime_error("Could not open out file");
	}


	int planar = av_sample_fmt_is_planar(avAudioCodec->sample_fmt);
	std::cout << "Planar: " << planar << std::endl;
	std::cout << "Sample fmt: " << avAudioCodec->sample_fmt << std::endl;
	while (av_read_frame(avFormat, &packet.packet) >= 0) {
		if (packet.packet.stream_index != audioStream->index) {
			std::cout << "Yup" << std::endl;
			continue;
		}

		int isFrameAvailable = 0;
		const auto processedLength = avcodec_decode_audio4(avAudioCodec.get(),
								   avFrame.get(),
								   &isFrameAvailable,
								   &packet.packet);
		if (processedLength < 0) {
			std::cout << processedLength << std::endl;
			throw std::runtime_error("Error while processing data");
		}

		if (isFrameAvailable) {
			int plane_size;
			int frame_size = av_samples_get_buffer_size(&plane_size,
								    avAudioCodec.get()->channels,
								    avFrame.get()->nb_samples,
								    avAudioCodec.get()->sample_fmt,
								    1);


			if (planar) {
				for (int ch = 0; ch < avAudioCodec.get()->channels; ch++) {
					fwrite(avFrame->extended_data[ch], 1, avFrame->linesize[ch], out);
				}
			} else {
				fwrite(avFrame->extended_data[0], 1, frame_size, out);
			}
		}

		offsetInData += processedLength;
	}



	return 0;
}

static std::shared_ptr<AVFormatContext> read_file(const char* infile) {
	std::shared_ptr<AVFormatContext> avFormat(avformat_alloc_context(), &avformat_free_context);

	auto avFormatPtr = avFormat.get();

	if (avformat_open_input(&avFormatPtr, infile, nullptr, nullptr) != 0) {
		throw std::runtime_error("Error opening the file");
	}

	if (avformat_find_stream_info(avFormat.get(), nullptr) < 0) {
		throw std::runtime_error("Error finding stream info");
	}

	return avFormat;
}

int main(int argc, char **argv) {
	init();

	const char* infile = "samples/goose.mp3";
	const char* outfile = "out.sw";

	auto avFormat = read_file(infile);
	FILE* out = fopen(outfile, "wb");

	decode_audio(avFormat, out);
	fclose(out);
}
