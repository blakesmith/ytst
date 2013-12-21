#ifndef YTST_PACKET_HPP
#define YTST_PACKET_HPP

extern "C" {
#include <libavformat/avformat.h>
}

namespace ytst {
	struct Packet {
		AVPacket packet;

		explicit Packet(AVFormatContext* ctxt);
		Packet(Packet&& other);
		~Packet();
		void reset(AVFormatContext* ctxt);
	};
}
#endif
