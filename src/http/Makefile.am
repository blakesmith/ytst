RAGEL=ragel
noinst_LTLIBRARIES = libytst_http.la

libytst_http_la_SOURCES = \
	http11_parser.h http11_parser.c \
	HttpServer.hpp HttpServer.cpp \
	HttpClient.hpp HttpClient.cpp \
	HttpParser.hpp HttpParser.cpp \
	HttpResponseWriter.hpp HttpResponseWriter.cpp \
	HttpResponseCodes.hpp HttpHandler.hpp \
	HttpHandler.cpp HttpRequest.hpp \
	RouteHandler.hpp RouteHandler.cpp 

http11_parser.c:
	$(RAGEL) http11_parser.rl

clean-local:
	rm -rf http11_parser.c

AM_CXXFLAGS = $(LIBEV_CFLAGS) -I$(srcdir) -I$(srcdir)/.. -I$(top_srcdir)
