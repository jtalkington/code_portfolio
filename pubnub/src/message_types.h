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

#ifndef __message_types_h_
#define __message_types_h_

#include <stdbool.h>
#include <stdint.h>

#include "process.h"

/**
 * The available message types.
 */
typedef enum message_type_t {
    MESSAGE_TYPE_DATA,
    MESSAGE_TYPE_CONTROL
} message_type_t;

/**
 * @brief The parsed contents of a message on the data channel.
 *
 * This is the data that is sent in a data_message message, in struct form.
 */
typedef struct data_message_t {
    /// The uuid of the processed message. Unfortunately the API does not expose
    /// time_token, so we have to generate it in the request. Exposing it in the
    /// API would be trivial, but I want this program to work with the existing
    /// code.
    uint64_t uuid;    

    /// The number of seconds for a worker to sleep.
    uint32_t sleepTime;

    /// The results of processing
    process_result_t result;

} data_message_t;

typedef struct control_message_t {
    /// The thread id of the worker 
    uint64_t workerId;

    /// The uuid of the processed message. Unfortunately the API does not expose
    /// time_token, so we have to generate it in the request. Exposing it in the
    /// API would be trivial, but I want this program to work with the existing
    /// code. 
    uint64_t uuid;

    /// The result of the processing.
    const char *result;

} control_message_t;


#endif // __message_types_h_

