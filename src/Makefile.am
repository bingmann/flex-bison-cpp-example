# $Id$

AM_CFLAGS = -W -Wall -Wextra -ansi
AM_CXXFLAGS = -W -Wall -Wextra -ansi

noinst_LIBRARIES = libexampleparser.a

libexampleparser_a_SOURCES = \
	parser.yy scanner.ll scanner.h driver.cc driver.h y.tab.h \
	location.hh position.hh stack.hh

bin_PROGRAMS = test
test_SOURCES = test.cc
LIBS = libexampleparser.a

# this output override is needed because the c++ scanner is outputted into
# lex.yy.cc and the automake ylwrap script only checks for lex.yy.c
AM_LFLAGS = -olex.yy.c
