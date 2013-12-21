#include <stdlib.h>
#include <utility>

#include "Packet.hpp"

namespace ytst {
	Packet::Packet(AVFormatContext* ctxt = nullptr) {
		av_init_packet(&packet);
		packet.data = nullptr;
		if (ctxt) {
			reset(ctxt);
		}
	}

	Packet::Packet(Packet&& other) : packet(std::move(other.packet)) {
		other.packet.data = nullptr;
	}

	Packet::~Packet() {
		if (packet.data) {
			av_free_packet(&packet);
		}
	}

	void Packet::reset(AVFormatContext* ctxt) {
		if (packet.data) {
			av_free_packet(&packet);
		}
		if (av_read_frame(ctxt, &packet) < 0) {
			packet.data = nullptr;
		}
	}
}
