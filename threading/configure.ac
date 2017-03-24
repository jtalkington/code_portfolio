AC_INIT([jtalkington-threads], [1.0.0], [jtalkington@gmail.com])


#AC_CONFIG_SRCDIR([src/
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIRS([m4])

AM_INIT_AUTOMAKE([-Wall -Werror no-exeext foreign subdir-objects])

AC_PROG_CC
AC_PROG_CXX
AC_LANG([C++])
AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_CPP
AX_PTHREAD

AX_BOOST_BASE
AX_BOOST_UNIT_TEST_FRAMEWORK


AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT
