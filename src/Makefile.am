ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

lib_LTLIBRARIES = libled.la
libled_la_SOURCES  = led.h
libled_la_SOURCES += led.cpp

include_HEADERS = led.h
libdir = $(prefix)/lib/yapiot/
includedir = $(prefix)/include/yapiot/libled

libledextradir = $(prefix)/lib/pkgconfig
libledextra_DATA = led.pc
