/*
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

#include <json.h>
#include <stdint.h>

#include "process.h"
#include "data_channel.h"

/**
 * @brief Create an data_message_t* object from a pubnub subscribe response.
 *
 * @param msg The message returned from a pubnub sync.
 * @returns A freshly allocated data_message_t pointer. It is the
 * responsibility of the caller to free.
 */
data_message_t* extract_data_message(json_object *msg);


