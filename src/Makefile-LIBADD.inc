include $(top_srcdir)/Array/src/Makefile-LIBADD.inc
#include $(top_srcdir)/swap/src/Makefile-LIBADD.inc

if USE_SUBMODULES
LIBCHEAP_LIBADD  = ../Array/src/.libs/libarray.la $(LIBARRAY_LIBADD)
#LIBCHEAP_LIBADD += ../swap/src/.libs/libswap.la $(LIBSWAP_LIBADD)
else
LIBCHEAP_LIBADD  = -larray $(LIBARRAY_LIBADD)
#LIBCHEAP_LIBADD += -lswap $(LIBSWAP_LIBADD)
endif
