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

#ifndef __listener_h_
#define __listener_h_

#include "process.h"

/**
 * @brief Initialize the subscriber context.
 * @returns PROCESS_FAILURE if initialization failed, otherwise PROCESS_SUCCESS.
 */
process_result_t listener_init(void);

/**
 * @brief Pull the messages from channel and send them to the processor, using
 * the sync API.
 * @returns Any error messages returned by pubnub.
 *
 * @TODO This should accept a callback function for processing instead of
 * relying on function named "process_message" to be linked in.
 */
int listener_loop(const char *channel);

#endif // __listener_h_

