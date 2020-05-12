AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#
#SUBDIRS += ../Array
#AM_CPPFLAGS += -I $(top_srcdir)/Array/src
#endif

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

#include Makefile-LIBADD.inc
dist_bin_SCRIPTS = libcheap_config cheap_test_config

lib_LTLIBRARIES += libcheap.la
#libcheap_la_LIBADD = $(LIBCHEAP_LIBADD)
libcheap_la_LIBADD = @LIBCHEAP_LIBADD@
include_HEADERS += cheap.h
#include ../../StD/src/Makefile-LIBADD.inc
bin_PROGRAMS += cheap-test
#cheap_test_LDADD = libcheap.la $(LIBCHEAP_LIBADD) -lsimon $(LIBSIMON_LIBADD)
#cheap_test_LDADD = $(CHEAP_TEST_LIBADD)
cheap_test_LDADD = @CHEAP_TEST_LIBADD@
EXTRA_cheap_test_DEPENDENCIES = libcheap.la
