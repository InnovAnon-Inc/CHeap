lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

lib_LTLIBRARIES += libcheap.la
libcheap_la_SOURCES = cheap.c
#libcheap_la_LIBADD = -lm
include_HEADERS += cheap.h
bin_PROGRAMS += cheap
cheap_SOURCES = cheap-test.c
#cheap_LDADD = libcheap.la -lm
cheap_LDADD = libcheap.la

AM_CPPFLAGS = -D__STDC_INT64__
AM_CPPFLAGS += -I $(srcdir)/../glitter/src
