# $Id$

AC_PREREQ(2.59)

AC_INIT([flex-bison-cpp-example], [0.1.4])
AC_CONFIG_SRCDIR([src/exprtest.cc])
AC_CONFIG_AUX_DIR([scripts])

AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

if test "$CFLAGS" == ""; then
    CFLAGS="-g -I/usr/include"
fi
if test "$CXXFLAGS" == ""; then
    CXXFLAGS="-g -I/usr/include"
fi

# enable full optimization by configure switch
AC_ARG_ENABLE(optimize,
	AS_HELP_STRING([--enable-optimize],
		       [Build with full optimization @<:@default=no@:>@]),
        [ case "${enableval}" in
          yes)
                CFLAGS="$CFLAGS -O3 -DNDEBUG";
                CXXFLAGS="$CXXFLAGS -O3 -DNDEBUG";
          ;;
          no) ;;
          *) AC_MSG_ERROR(bad value ${enableval} for --enable-optimize) ;;
          esac ],
        [ optimize=false ])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AC_PROG_LEX
AC_PROG_YACC

# Create Makefiles
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
