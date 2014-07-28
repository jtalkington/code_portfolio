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

/**
 * Extract a uint32_t from data channel message by name.
 *
 * @param msg The message to extract the data from.
 * @param key The key to extract.
 * @param dst A pointer to an int to place the value in.
 */
process_result_t json_get_int(json_object *msg, const char *key, uint32_t *dst);

/**
 * Extract a uint64_t from data channel message by name.
 *
 * @param msg The message to extract the data from.
 * @param key The key to extract.
 * @param dst A pointer to an int to place the value in.
 */
process_result_t json_get_uint64(json_object *msg, const char *key, uint64_t *dst);

/**
 * @brief Get a json string from an object.
 *
 * @param msg The object that contains the string.
 * @param key The name of the string to extract.
 *
 * Retreives a const char * string from a container, instead of having to
 * extract it as an object before extracting the string.
 */
const char *json_get_string(json_object *msg, const char *key);
