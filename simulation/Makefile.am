ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

bin_PROGRAMS = ledtest

ledtest_CFLAGS = -DTESTFIRMWARE $(AM_CFLAGS)
ledtest_CXXFLAGS = -DTESTFIRMWARE $(AM_CXXFLAGS)
ledtest_SOURCES  = ../src/test.cpp
ledtest_SOURCES += simulate.cpp
ledtest_LDADD = $(top_builddir)/src/libled.la $(ARDSIM_LIBS)
