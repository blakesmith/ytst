#include <stdlib.h>
#include <iostream>
#include <mutex>
#include <memory>

extern "C" {
#include <libavformat/avformat.h>
}

#include "Packet.hpp"

int main(int argc, char **argv) {
	static std::once_flag initFlag;
	std::call_once(initFlag, []() { av_register_all(); });

	std::shared_ptr<AVFormatContext> avFormat(avformat_alloc_context(), &avformat_free_context);

	auto avFormatPtr = avFormat.get();
	
	if (avformat_open_input(&avFormatPtr, "samples/bangarang.mp4", nullptr, nullptr) != 0) {
		throw std::runtime_error("Error opening the file");
	}

	if (avformat_find_stream_info(avFormat.get(), nullptr) < 0) {
		throw std::runtime_error("Error finding stream info");
	}

	std::cout << "Codec ids found: " << std::endl;
	for (unsigned int i = 0; i < avFormat->nb_streams; ++i) {
		auto stream = avFormat->streams[i];
		// auto codecType = stream->codec->codec_type;
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

	ytst::Packet packet(avFormat.get());
	do {
		packet.reset(avFormat.get());
		if (packet.packet.stream_index != audioStream->index) {
			continue;
		}
	} while (0);

	return 0;
}
