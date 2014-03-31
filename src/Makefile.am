SUBDIRS = http python
EXTRA_DIST=ytst.init python/youtube-dl
RAGEL=ragel
AM_CXXFLAGS=$(ffmpeg_CFLAGS) $(PYTHON_CPPFLAGS) $(PTHREAD_CFLAGS) -Wall -pedantic -D__STDC_CONSTANT_MACROS
bin_PROGRAMS=ytst
ytst_C_SOURCES = uuid.h uuid.c
ytst_SOURCES= \
	$(ytst_C_SOURCES) \
	Main.cpp \
	Log.hpp \
	Encoder.hpp \
	Packet.hpp Packet.cpp \
	Decoder.hpp Decoder.cpp \
	MP3Encoder.hpp MP3Encoder.cpp \
	Stream.hpp Stream.cpp \
	CmdOpt.hpp CmdOpt.cpp \
	Buffer.hpp Buffer.cpp \
	Writer.hpp \
	BufferedWriter.hpp BufferedWriter.cpp

ytst_LDADD=$(LIBEV_LIBS) $(ffmpeg_LIBS) $(PYTHON_LDFLAGS) $(PTHREAD_LDFLAGS) \
	http/libytst_http.la \
	python/libytst_python.la \
	youtube/libytst_youtube.la

install-exec-hook:
	cp $(srcdir)/ytst.init /etc/init.d/ytst
	mkdir -p $(prefix)/lib/ytst
	cp -rv $(srcdir)/python $(prefix)/lib/ytst

uninstall-hook:
	rm -f /etc/init.d/ytst
	rm -rf $(prefix)/lib/ytst


