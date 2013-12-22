#ifndef YTST_PACKET_HPP
#define YTST_PACKET_HPP

extern "C" {
#include <libavformat/avformat.h>
}

namespace ytst {
	struct Packet {
		AVPacket packet;

		Packet();
		Packet(Packet&& other);
		~Packet();
		void reset();
	};
}
#endif
