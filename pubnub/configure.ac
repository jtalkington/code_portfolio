#/*
# Copyright 2014 Jerry Talkington
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#  http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#*/

AC_INIT([pubnub-example], 1.0.0, jtalkington@users.noreply.github.com)

AC_DEFINE([PUBNUB_MESSAGE_CHANNEL], "code_portfolio_pubnub_test", [The PubNub channel to use.])
AC_SUBST([PUBNUB_MESSAGE_CHANNEL], "code_portfolio_pubnub_test")

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign subdir-objects])

AC_ARG_WITH([subkey], 
    AS_HELP_STRING([--with-subkey=KEY], [Set the PubNub subkey key.]))

AS_IF([test "x${with_subkey}" != "x"],
    [AC_DEFINE_UNQUOTED([PUBNUB_SUBSCRIBE_KEY], ["${with_subkey}"], [PubNub Subscription Key])],
    [AC_MSG_ERROR([Must define PubNub subscribe key using --with-subkey=KEY])]
)

AC_SUBST([PUBNUB_SUBSCRIBE_KEY], "${with_subkey}")

AC_ARG_WITH([pubkey], 
    AS_HELP_STRING([--with-pubkey=KEY], [Set the PubNub pubkey key.]))

AS_IF([test "x${with_pubkey}" != "x"],
    [AC_DEFINE_UNQUOTED([PUBNUB_PUBLISH_KEY], ["${with_pubkey}"], [PubNub Publish Key])],
    [AC_MSG_ERROR([Must define PubNub publish key using --with-pubkey=KEY])]
)

AC_SUBST([PUBNUB_PUBLISH_KEY], "${with_pubkey}")

AC_DEFINE([ENABLE_DEBUG], [0], [Enable debugging output.])

AC_ARG_ENABLE([debug], 
    AS_HELP_STRING([--enable-debug], [Enable debugging output.]),
    [AC_DEFINE([ENABLE_DEBUG], [1])]
)

LT_INIT
AC_PROG_CC_C99
AC_PROG_LD
AC_PROG_INSTALL
AC_PROG_LIBTOOL

PKG_CHECK_EXISTS("json-c", [AC_SUBST([JSON], "json-c")],
    [PKG_CHECK_EXISTS("json", [AC_SUBST([JSON], "json")])])

AC_SUBST([PKGS_REQUIRED], "${JSON} libpubnub libcurl") 

PKG_CHECK_MODULES([PKGS], "${PKGS_REQUIRED}")

AC_SUBST([CONF_CPPFLAGS], "${PKGS_CFLAGS}")
AC_SUBST([CONF_LDFLAGS], "${PKGS_LIBS}")

# Test for the check library, and enable tests if it exists.

PKG_CHECK_MODULES([TEST], "check", , [AC_SUBST([DISABLE_TEST])])

AM_CONDITIONAL([ENABLE_TEST], [test "x$TEST_CFLAGS" != "x"])

AC_SUBST([TEST_CPPFLAGS], "${TEST_CFLAGS}")
AC_SUBST([TEST_LDFLAGS], "${TEST_LIBS}")

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/channel_flood.py], [chmod +x src/channel_flood.py])
AC_CONFIG_HEADERS([config.h])
AC_OUTPUT
