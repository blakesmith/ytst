# http_url:

check_PROGRAMS = http_url_check
http_url_check_SOURCES = http_url_check.cc
http_url_check_LDFLAGS = -L$(top_builddir)/src \
	$(top_builddir)/src/http/http_url.lo
http_url_check_CXXFLAGS = -I$(top_srcdir)/src/http

TESTS = $(check_PROGRAMS)
