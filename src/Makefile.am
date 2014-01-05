RAGEL=ragel
AM_CXXFLAGS=$(LIBEV_CFLAGS) $(ffmpeg_CFLAGS) $(PYTHON_CPPFLAGS) $(PTHREAD_CFLAGS) -Wall -pedantic
bin_PROGRAMS=ytst
ytst_SOURCES=Main.cpp Packet.hpp Packet.cpp Decoder.hpp Decoder.cpp FileWriter.hpp FileWriter.cpp MP3Encoder.hpp MP3Encoder.cpp YTDownloader.hpp YTDownloader.cpp Python.hpp Python.cpp Stream.hpp Stream.cpp
ytst_LDADD=$(LIBEV_LIBS) $(ffmpeg_LIBS) $(PYTHON_LDFLAGS) $(PTHREAD_LDFLAGS)

http11/http11_parser.c:
	$(RAGEL) http11/http11_parser.rl

clean-local:
	rm -rf http/http11_parser.c

