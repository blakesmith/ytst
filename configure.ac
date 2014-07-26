#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([YTST], [0.0.16])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

LT_INIT([disable-static])

# Checks for programs.
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

AX_PYTHON_DEVEL([">= 2.7.2"])

AX_PTHREAD([],[mandatory])

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Checks for packages which use pkg-config.
# PKG_CHECK_MODULES([libev], [libev >= 4.11])


# lib ev
# stollen from lighttpd's configure.ac
AC_MSG_CHECKING([for libev support])
AC_ARG_WITH([libev],
    [AS_HELP_STRING([--with-libev@<:@=PATH@:>@],[Search for libev in PATH/include and PATH/lib])],
    [WITH_LIBEV=$withval],[WITH_LIBEV=yes])

LIBEV_CFLAGS=""
LIBEV_LIBS=""

PKG_CHECK_MODULES([LIBEV], [libev], [], [
# no pkg-config for libev, searching manually:
  if test "$WITH_LIBEV" != "yes"; then
     LIBEV_CFLAGS="-I$WITH_LIBEV/include"
     LIBEV_LIBS="-L$WITH_LIBEV/lib -lev"
  else
     AC_CHECK_HEADERS([ev.h],[
     AC_CHECK_LIB([ev], [ev_time], [
     LIBEV_LIBS="-lev"
     ],[AC_MSG_ERROR([libev not found])])],[
     AC_MSG_ERROR([libev not found])])
  fi
])

AC_SUBST([LIBEV_CFLAGS])
AC_SUBST([LIBEV_LIBS])

# Other tools used in this package's various make scripts
AC_PATH_PROG([PERL], [perl])      # Perl
AC_PATH_PROG([TAR], [tar gtar])   # tar
AC_PATH_PROG([XARGS], [xargs])    # xargs
AC_PATH_PROG([CHMOD], [chmod])    # chmod
AC_PATH_PROG([CAT], [cat])        # cat
AC_PATH_PROG([ECHO], [echo])      # echo
AC_PATH_PROG([CP], [cp])          # cp
AC_PATH_PROG([DATE], [date])      # date
AC_PATH_PROG([MV], [mv])          # mv
AC_PATH_PROG([TEST], [test])

AC_PATH_PROG([DEBUILD], [dpkg-buildpackage], [notfound])

# --enable-deb copies only the ni executable to the dist package, for use in
# building DEB packages.
AC_ARG_ENABLE([deb],
	[AS_HELP_STRING([--enable-deb=@<:@yes/no@:>@],
		[Configure for building Debian package @<:@default=no@:>@ (requires dpkg-buildpackage)])],
	[AS_IF([$TEST "x$enable_deb" = xyes],
	        [AS_IF([$TEST "x$DEBUILD" = xnotfound],
			      [AC_MSG_ERROR([dpkg-buildpackage is required for --enable-deb])])])],
	[enable_deb=no])

AM_CONDITIONAL([BUILDING_DEB], [$TEST "x$enable_deb" = xyes])

PKG_CHECK_MODULES(ffmpeg, libavutil libavformat libavcodec, HAVE_FFMPEG=yes)


AC_CONFIG_FILES([Makefile
                 src/Makefile
		 src/http/Makefile
		 src/ev/Makefile
		 src/python/Makefile
		 src/youtube/Makefile
		 src/stream/Makefile
		 test/Makefile])
AC_OUTPUT
