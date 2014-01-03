RAGEL=ragel
AM_CXXFLAGS=$(LIBEV_CFLAGS) $(ffmpeg_CFLAGS) $(PYTHON_CPPFLAGS) -Wall -pedantic
bin_PROGRAMS=ytst
ytst_SOURCES=Main.cpp Packet.hpp Packet.cpp Decoder.hpp Decoder.cpp FileEncoder.hpp FileEncoder.cpp MP3Encoder.hpp MP3Encoder.cpp YTDownloader.hpp YTDownloader.cpp
ytst_LDADD=$(LIBEV_LIBS) $(ffmpeg_LIBS) $(PYTHON_LDFLAGS)

http11/http11_parser.c:
	$(RAGEL) http11/http11_parser.rl

clean-local:
	rm -rf http/http11_parser.c

