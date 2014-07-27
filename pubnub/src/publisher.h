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

#include <json.h>
#include "process.h"

/**
 * @brief Initialize the publisher context.
 * @returns PROCESS_FAILURE if initialization failed, otherwise PROCESS_SUCCESS.
 */
process_result_t publisher_init(void);

/**
 * @brief Publish a message on the publisher context.
 *
 * @param channel The channel to publish on.
 * @param msg The json message to send.
 */
process_result_t publish_message(const char *channel, json_object *msg);
