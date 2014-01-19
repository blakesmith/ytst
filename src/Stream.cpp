#include <thread>
#include <iostream>

extern "C" {
#include "uuid.h"
}

#include "Log.hpp"
#include "YTDownloader.hpp"
#include "Decoder.hpp"
#include "MP3Encoder.hpp"
#include "Packet.hpp"

#include "Stream.hpp"

const size_t UUID_LENGTH = 36;

namespace ytst {
	Stream::Stream(std::string fifo_directory,
		       std::shared_ptr<ytst::Python> python,
		       Writer* writer) {
		this->fifo_directory = fifo_directory;
		this->python = python;
		this->writer = writer;
	}

	Stream::~Stream() {
		if (dt.joinable()) {
			dt.join();
		}
	}

	void Stream::stream(std::string id) {
		std::string infile = fifo_location();
		std::string url = youtube_url(id);

		ytst::Stream::Fifo fifo(infile);

		LOG(logINFO) << "Starting video download";
		dt = std::thread([=] {
				ytst::YTDownloader downloader(url, infile, python);
				downloader.download();
			});

		LOG(logINFO) << "Starting decoder";
		ytst::Decoder decoder(infile);
		auto decoder_ctxt = decoder.read_file();

		LOG(logINFO) << "Starting encoder";
		ytst::MP3Encoder encoder(decoder_ctxt);
		encoder.open_encoder();
		
		AVFrame* frame;
		ytst::Packet packet;
		LOG(logINFO) << "Begin decoding";

		while ((frame = decoder.decode_frame()) != nullptr) {
			try {
				encoder.encode_frame(frame, packet);
				auto buf = new Buffer(reinterpret_cast<const char*>(packet.packet.data),
						      packet.packet.size);
				writer->write_buffer(buf);
				packet.reset();
			} catch(std::runtime_error e) {
				LOG(logERROR) << "Encoding exception: " << e.what();
			}
		}
		LOG(logINFO) << "Done decoding";
	}

	std::string Stream::youtube_url(std::string id) {
		return std::string("https://www.youtube.com/watch?v=") + id;
	}

	std::string Stream::fifo_location() {
		// XXX: Not OS independent!
		return std::string(fifo_directory + "/" + stream_id() + ".mp4");
	}
	
	std::string Stream::stream_id() {
		char buf[UUID_LENGTH];
		afsUUID uuid;

		uuid_create(&uuid);
		uuid_to_string(&uuid, buf, UUID_LENGTH);

		return std::string(buf, UUID_LENGTH);
	}
}
