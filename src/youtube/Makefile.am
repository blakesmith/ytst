noinst_LTLIBRARIES = libytst_youtube.la

libytst_youtube_la_SOURCES = \
	youtube_downloader.h youtube_downloader.cc \
	youtube_handler.h youtube_handler.cc \
	youtube_stream.h youtube_stream.cc

AM_CXXFLAGS = $(ffmpeg_CFLAGS) $(PYTHON_CPPFLAGS) $(PTHREAD_CFLAGS) -D__STDC_CONSTANT_MACROS -I$(srcdir) -I$(srcdir)/.. -I$(top_srcdir)
