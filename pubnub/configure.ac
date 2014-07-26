AC_INIT([pubnub-example], 1.0.0, jtalkington@users.noreply.github.com)

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign subdir-objects])

LT_INIT
AC_LANG([C++])
AC_PROG_CC
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_LD
AC_PROG_INSTALL
AC_PROG_LIBTOOL

PKG_CHECK_EXISTS("json-c", [AC_SUBST([JSON], "json-c")],
    [PKG_CHECK_EXISTS("json", [AC_SUBST([JSON], "json")])])

AC_SUBST([PKGS_REQUIRED], "${JSON} libpubnub libcurl") 

PKG_CHECK_MODULES([PKGS], "${PKGS_REQUIRED}")

AC_SUBST([CONF_CPPLAGS], "${PKGS_CFLAGS}")
AC_SUBST([CONF_LDFLAGS], "${PKGS_LIBS}")

AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADERS([config.h])
AC_OUTPUT
