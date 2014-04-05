SUBDIRS = http python youtube stream ev
EXTRA_DIST=ytst.init python/youtube-dl
RAGEL=ragel
AM_CXXFLAGS=$(ffmpeg_CFLAGS) $(PYTHON_CPPFLAGS) $(PTHREAD_CFLAGS) -Wall -pedantic -D__STDC_CONSTANT_MACROS
bin_PROGRAMS=ytst
ytst_C_SOURCES = uuid.h uuid.c
ytst_SOURCES= \
	$(ytst_C_SOURCES) \
	main.cc \
	log.h \
	cmd_opt.h cmd_opt.cc \
	buffer.h buffer.cc \
	writer.h \
	buffered_writer.h buffered_writer.cc \
	socket_desc.h socket_desc.cc

ytst_LDADD= \
	youtube/libytst_youtube.la \
	stream/libytst_stream.la \
	http/libytst_http.la \
	ev/libytst_ev.la \
	python/libytst_python.la \
	$(LIBEV_LIBS) $(ffmpeg_LIBS) $(PYTHON_LDFLAGS) $(PTHREAD_LDFLAGS)

install-exec-hook:
	cp $(srcdir)/ytst.init /etc/init.d/ytst
	mkdir -p $(prefix)/lib/ytst
	cp -rv $(srcdir)/python $(prefix)/lib/ytst

uninstall-hook:
	rm -f /etc/init.d/ytst
	rm -rf $(prefix)/lib/ytst


