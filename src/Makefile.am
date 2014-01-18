EXTRA_DIST=ytst.init python/youtube-dl
RAGEL=ragel
AM_CXXFLAGS=$(LIBEV_CFLAGS) $(ffmpeg_CFLAGS) $(PYTHON_CPPFLAGS) $(PTHREAD_CFLAGS) -Wall -pedantic -D__STDC_CONSTANT_MACROS
bin_PROGRAMS=ytst
ytst_C_SOURCES = http11_parser.h http11_parser.c uuid.h uuid.c
ytst_SOURCES=Python.hpp Python.cpp $(ytst_C_SOURCES) Main.cpp Log.hpp Encoder.hpp Packet.hpp Packet.cpp Decoder.hpp Decoder.cpp FileWriter.hpp FileWriter.cpp MP3Encoder.hpp MP3Encoder.cpp YTDownloader.hpp YTDownloader.cpp Stream.hpp Stream.cpp CmdOpt.hpp CmdOpt.cpp HttpServer.hpp HttpServer.cpp HttpClient.hpp HttpClient.cpp Buffer.hpp Buffer.cpp Writer.hpp BufferedWriter.hpp BufferedWriter.cpp HttpParser.hpp HttpParser.cpp HttpResponseWriter.hpp HttpResponseWriter.cpp HttpResponseCodes.hpp
ytst_LDADD=$(LIBEV_LIBS) $(ffmpeg_LIBS) $(PYTHON_LDFLAGS) $(PTHREAD_LDFLAGS)

install-exec-hook:
	cp $(srcdir)/ytst.init /etc/init.d/ytst
	mkdir $(prefix)/usr/local/lib/ytst
	cp -rv $(srcdir)/python $(prefix)/usr/local/lib/ytst

uninstall-hook:
	rm -f /etc/init.d/ytst

http11_parser.c:
	$(RAGEL) http11_parser.rl

clean-http:
	rm -rf http11_parser.c

