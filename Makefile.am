# $Id$

AM_CFLAGS = -W -Wall -Wextra -ansi
AM_CXXFLAGS = -W -Wall -Wextra -ansi
AM_CPPFLAGS = -Isrc -I$(srcdir)/src

noinst_LIBRARIES = libexampleparser.a

BUILT_SOURCES = src/parser.cc src/parser.hh src/scanner.cc

libexampleparser_a_SOURCES = \
	src/parser.yy src/scanner.ll src/scanner.h src/y.tab.h \
	src/location.hh src/position.hh src/stack.hh src/FlexLexer.h \
	src/driver.cc src/driver.h src/expression.h

bin_PROGRAMS = exprtest

exprtest_SOURCES = src/exprtest.cc
exprtest_LDADD = libexampleparser.a

LIBS = libexampleparser.a

# this output override is needed because the c++ scanner is outputted into
# lex.yy.cc and the automake ylwrap script only checks for lex.yy.c
AM_LFLAGS = -olex.yy.c

EXTRA_DIST = src/readme.dox src/exprtest.txt \
	     src/exprtest.vcproj src/libexampleparser.vcproj \
	     src/Makefile.plain

EXTRA_DIST += Doxyfile doxygen.css doxygen-html/* \
	      flex-bison-cpp-example.sln

extraclean:
	rm -f src/parser.cc src/parser.h src/scanner.cc

rebuild: clean extraclean all
