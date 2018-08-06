ACLOCAL_AMFLAGS = -I $(top_srcdir)/m4

include $(top_srcdir)/utests/Makefile.test.common

SUBDIRS = fixtures

TESTS = ut_led.xtest

noinst_PROGRAMS = $(TESTS)

check_PROGRAMS = $(TESTS)

lib_LTLIBRARIES = libled_utests.la
libled_utests_la_CFLAGS = $(TESTCFLAGS)
libled_utests_la_CXXFLAGS = $(TESTCXXFLAGS)
libled_utests_la_SOURCES  = ../src/led.h
libled_utests_la_SOURCES += ../src/led.cpp

ut_led_xtest_SOURCES  = ut_led.h
ut_led_xtest_SOURCES += ut_led_rgb.h
ut_led_xtest_SOURCES += main.cpp
ut_led_xtest_CFLAGS = $(TESTCFLAGS)
ut_led_xtest_CXXFLAGS = $(TESTCXXFLAGS)
ut_led_xtest_LDFLAGS = $(TESTLDFLAGS)
ut_led_xtest_LDADD  = $(top_builddir)/utests/libled_utests.la
ut_led_xtest_LDADD += $(top_builddir)/utests/fixtures/libfixtures.la
