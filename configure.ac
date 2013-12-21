#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([YTST], [0.01])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([src/Main.cpp])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

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


PKG_CHECK_MODULES(ffmpeg, libavutil libavformat libavcodec, HAVE_FFMPEG=yes)


AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
