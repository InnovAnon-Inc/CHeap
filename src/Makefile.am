AM_CPPFLAGS = -D__STDC_INT64__

lib_LTLIBRARIES =
include_HEADERS =
bin_PROGRAMS    =

lib_LTLIBRARIES += libcheap.la
libcheap_la_CPPFLAGS = $(GLITTER_CFLAGS) $(ARRAY_CFLAGS)
libcheap_la_LIBADD   = $(GLITTER_LIBS)   $(ARRAY_LIBS)
include_HEADERS += cheap.h

bin_PROGRAMS += cheap-test
cheap_test_CPPFLAGS =         $(GLITTER_CFLAGS) $(ARRAY_CFLAGS) $(SIMON_CFLAGS)
cheap_test_LDADD    = -lcheap $(GLITTER_LIBS)   $(ARRAY_LIBS)   $(SIMON_LIBS)
EXTRA_cheap_test_DEPENDENCIES = libcheap.la

