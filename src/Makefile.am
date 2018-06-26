ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/Makefile.common

lib_LTLIBRARIES = libled.la
libled_la_SOURCES  = led.h
libled_la_SOURCES += led.cpp

include_HEADERS = led.h

bin_PROGRAMS = ledtest

ledtest_SOURCES  = test.cpp
ledtest_SOURCES += simulate.cpp
ledtest_LDADD = libled.la
