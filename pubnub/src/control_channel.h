 /*
# * Copyright 2014 Jerry Talkington
# *  
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# */

#ifndef __control_channel_h_
#define __control_channel_h_

#include <stdbool.h>
#include "process.h"

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

/**
 * @brief Creates a control_message_t object and returns it's pointer to the
 * caller.
 *
 * @param dataMsg The data_message_t object that was processed.
 * @param result The result of the processing.
 */
control_message_t* create_control_message(data_message_t *dataMsg);

/**
 * @brief Initialize the control channel.
 *
 * @returns A process_result_t result code.
 */
process_result_t control_channel_init();

/**
 * @brief Publish and free a control message.
 *
 * @param msg The message to publish.
 * @returns The result of the request.
 */
process_result_t publish_control_message(control_message_t *msg);

#endif // __control_channel_h_

