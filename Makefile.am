# Install the pkg-config file.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = src/libcheap.pc src/cheap-test.pc

DISTCLEANFILES = $(pkgconfig_DATA)
EXTRA_DIST = src/libcheap.pc.in src/cheap-test.pc.in

SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4

