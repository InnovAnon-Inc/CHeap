include $(top_srcdir)/Array/src/Makefile-LIBADD.inc
LIBCHEAP_LIBADD  = ../Array/src/.libs/libarray.la $(LIBARRAY_LIBADD)
include $(top_srcdir)/swap/src/Makefile-LIBADD.inc
LIBCHEAP_LIBADD += ../swap/src/.libs/libswap.la $(LIBSWAP_LIBADD)
