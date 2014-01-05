#include <thread>

#include "YTDownloader.hpp"
#include "Decoder.hpp"
#include "FileWriter.hpp"
#include "MP3Encoder.hpp"
#include "Packet.hpp"

#include "Stream.hpp"

namespace ytst {
	Stream::Stream(std::string fifo_directory) {
		this->fifo_directory = fifo_directory;
	}

	void Stream::stream(std::string id) {
		std::string infile = fifo_location();
		std::string url = youtube_url(id);

		ytst::Stream::Fifo fifo;
		fifo.create(infile);

		std::thread dt([=] { 
				ytst::YTDownloader downloader(url, infile);
				downloader.download();
			});
	
		ytst::Decoder decoder(infile);
		auto decoder_ctxt = decoder.read_file();

		ytst::MP3Encoder encoder(decoder_ctxt);
		encoder.open_encoder();

		const char* outfile = "download.mp3";
		FILE* out = fopen(outfile, "wb");
		ytst::FileWriter writer(out);

		AVFrame* frame;
		ytst::Packet packet;
		while ((frame = decoder.decode_frame()) != nullptr) {
			encoder.encode_frame(frame, packet);
			writer.write_packet(packet);
			packet.reset();
		}

		dt.join();
	}

	std::string Stream::youtube_url(std::string id) {
		return (std::string("https://www.youtube.com/watch?v=") + id);
	}

	std::string Stream::fifo_location() {
		// XXX: Not OS independent!
		return (fifo_directory + "/" + stream_id() + ".mp4");
	}
	
	std::string Stream::stream_id() {
		return "download";
	}
}
