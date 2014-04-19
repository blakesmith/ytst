RAGEL=ragel
noinst_LTLIBRARIES = libytst_http.la

libytst_http_la_SOURCES = \
	http11_parser.h http11_parser.c \
	http_server.h http_server.cc \
	http_client.h http_client.cc \
	HttpParser.hpp http_parser.cc \
	HttpResponseWriter.hpp http_response_writer.cc \
	HttpResponseCodes.hpp \
	http_handler.h http_handler.cc \
	http_request.h \
	http_route_handler.h http_route_handler.cc \
	http_url.h http_url.cc \
	ping_handler.h ping_handler.cc

http11_parser.c:
	$(RAGEL) http11_parser.rl

clean-local:
	rm -rf http11_parser.c

AM_CXXFLAGS = $(LIBEV_CFLAGS) -I$(srcdir) -I$(srcdir)/.. -I$(top_srcdir)
