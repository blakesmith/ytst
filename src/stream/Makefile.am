noinst_LTLIBRARIES = libytst_stream.la

libytst_stream_la_SOURCES = \
	encoder.h \
	decoder.h decoder.cc \
	mpeg_encoder.h mpeg_encoder.cc \
	packet.h packet.cc

AM_CXXFLAGS = $(ffmpeg_CFLAGS) $(PYTHON_CPPFLAGS) $(PTHREAD_CFLAGS) -D__STDC_CONSTANT_MACROS -I$(srcdir) -I$(srcdir)/.. -I$(top_srcdir)
