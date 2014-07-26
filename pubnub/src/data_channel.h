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

#ifndef __data_channel_h_
#define __data_channel_h_

#include <stdbool.h>
#include <stdint.h>

#include "process.h"

/**
 * @brief The parsed contents of a message on the data channel.
 *
 * This is the data that is sent in a data_channel message, in struct form.
 */
typedef struct data_message_t {
    /// The unique id of this message.
    uint64_t uuid;

    /// The number of seconds for a worker to sleep.
    uint32_t sleepTime;

    /// The results of processing
    process_result_t result;

} data_message_t;

#endif // __data_channel_h_

