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

bin_pubnub_listener_SOURCES = src/main_listener.c \
							 src/listener.c \
							 src/data_channel_process.c \
							 src/data_channel_worker.c \
							 src/control_channel.c \
							 src/pubnub_init.c \
							 src/process.c \
							 src/publisher.c
