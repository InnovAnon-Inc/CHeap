lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

LIBCHEAP_LIBADD  = ../Array/src/.libs/libarray.la $(LIBARRAY_LIBADD)
LIBCHEAP_LIBADD += ../swap/src/.libs/libswap.la $(LIBSWAP_LIBADD)

lib_LTLIBRARIES += libcheap.la
libcheap_la_SOURCES = cheap.c
libcheap_la_LIBADD = $(LIBCHEAP_LIBADD)
include_HEADERS += cheap.h
bin_PROGRAMS += cheap-test
cheap_test_LDADD = libcheap.la $(LIBCHEAP_LIBADD)

AM_CPPFLAGS = -D__STDC_INT64__

SUBDIRS = ../glitter
AM_CPPFLAGS += -I $(srcdir)/../glitter/src

SUBDIRS += ../Array
AM_CPPFLAGS += -I ../Array/src
