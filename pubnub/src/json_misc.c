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
#include "log.h"
#include "json_misc.h"

process_result_t json_get_int(json_object *msg, const char *key, uint32_t *dst) {
    json_object *tmpJson = NULL;

    if (!json_object_object_get_ex(msg, key, &tmpJson)) {
        LOG_ERROR("Could not read \"%s\" from message.\n", key);
        return PROCESS_FAILURE;
    }

    // Ugh, no way to check there result of this.
    *dst = (uint32_t)json_object_get_int(tmpJson);

    return PROCESS_SUCCESS;
}

process_result_t json_get_uint64(json_object *msg, const char *key, uint64_t *dst) {
    
    json_object *tmpJson = NULL;

    if (!json_object_object_get_ex(msg, key, &tmpJson)) {
        LOG_ERROR("Could not read \"%s\" from message.\n", key);
        return PROCESS_FAILURE;
    }

    json_parse_int64(json_object_get_string(tmpJson), (int64_t *)dst);

    return PROCESS_SUCCESS;
}

const char *json_get_string(json_object *msg, const char *key) {
    
    json_object *tmpJson;
    if(!json_object_object_get_ex(msg, key, &tmpJson)) {
        return NULL;
    }

    return json_object_get_string(tmpJson);
}
