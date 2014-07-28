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

AM_CPPFLAGS = -Wall -Werror ${CONF_CPPFLAGS}
AM_LDFLAGS = ${CONF_LDFLAGS}
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = bin/pubnub_listener

source_files =  src/listener.c \
				src/data_message.c \
				src/worker.c \
				src/control_message.c \
				src/pubnub_init.c \
				src/process.c \
				src/publisher.c \
				src/json_misc.c \
				src/fifo.c

bin_pubnub_listener_SOURCES = src/main_listener.c ${source_files}

if ENABLE_TEST
check_PROGRAMS = bin/test_queue bin/test_control_channel
TESTS = $(check_PROGRAMS)
bin_test_queue_SOURCES = test/test_queue.c
bin_test_queue_CPPFLAGS = $(AM_CPPFLAGS) ${TEST_CFLAGS}
bin_test_queue_LDFLAGS = $(AM_LDFLAGS) ${TEST_LDFLAGS}

bin_test_control_channel_SOURCES = test/test_control_message.c \
								   test/unit_test_main.c \
								   test/test_data_message.c \
								   ${source_files}
bin_test_control_channel_CPPFLAGS = $(AM_CPPFLAGS) ${TEST_CFLAGS}
bin_test_control_channel_LDFLAGS = $(AM_LDFLAGS) ${TEST_LDFLAGS}

endif

