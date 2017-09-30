AM_CPPFLAGS = -D__STDC_INT64__

if USE_SUBMODULES
SUBDIRS = ../glitter
AM_CPPFLAGS += -I $(top_srcdir)/glitter/src

SUBDIRS += ../Array
AM_CPPFLAGS += -I $(top_srcdir)/Array/src
endif

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

include Makefile-LIBADD.inc

lib_LTLIBRARIES += libcheap.la
libcheap_la_SOURCES = cheap.c
libcheap_la_LIBADD = $(LIBCHEAP_LIBADD)
include_HEADERS += cheap.h
bin_PROGRAMS += cheap-test
cheap_test_LDADD = libcheap.la $(LIBCHEAP_LIBADD)
