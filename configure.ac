# $Id$

AC_PREREQ(2.59)

AC_INIT([flex-bison-c++-example], [0.1])
AC_CONFIG_SRCDIR([src/test.cc])
AC_CONFIG_AUX_DIR([scripts])

AM_INIT_AUTOMAKE(foreign)
# AM_MAINTAINER_MODE

if test "$CFLAGS" == ""; then
    CFLAGS="-g -I/usr/include"
fi
if test "$CXXFLAGS" == ""; then
    CXXFLAGS="-g -I/usr/include"
fi

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AC_PROG_LEX
AC_PROG_YACC

# Create Makefiles
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT