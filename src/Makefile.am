RAGEL=ragel
AM_CXXFLAGS=$(LIBEV_CFLAGS) $(ffmpeg_CFLAGS) -Wall -pedantic
bin_PROGRAMS=ytst
ytst_SOURCES=Main.cpp 
ytst_LDADD=$(LIBEV_LIBS) $(ffmpeg_LIBS)

http11/http11_parser.c:
	$(RAGEL) http11/http11_parser.rl

clean-local:
	rm -rf http/http11_parser.c

