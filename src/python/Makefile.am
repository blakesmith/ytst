noinst_LTLIBRARIES = libytst_python.la

libytst_python_la_SOURCES = \
	python_executor.h python_executor.cc \
	python_supervisor.h python_supervisor.cc

AM_CXXFLAGS = $(PYTHON_CPPFLAGS) $(PTHREAD_CFLAGS) -I$(srcdir) -I$(srcdir)/.. -I$(top_srcdir)
