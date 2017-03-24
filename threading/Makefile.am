ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/include
AM_CFLAGS = ${PTHREAD_CFLAGS}
AM_CXXFLAGS = ${PTHREAD_CFLAGS}

library_headers = \
	include/LoggerBase.hpp \
	include/Logger.hpp \
	include/SumDigits.hpp

library_sources = \
	$(library_headers) \
	src/SumDigitsImpl.hpp \
	src/SumDigitsImpl.cpp \
	src/LoggerBase.cpp \
	src/SumDigits.cpp


check_PROGRAMS = bin/unittest
noinst_PROGRAMS = $(check_PROGRAMS)

bin_unittest_SOURCES = \
	$(library_sources) \
	tests/test_Logger.cpp \
	tests/test_SumDigits.cpp \
	tests/unittest.cpp
bin_unittest_LDFLAGS = -static ${BOOST_UNIT_TEST_FRAMEWORK_LIB}


TESTS = $(check_PROGRAMS)

