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
#include "data_channel_worker.h"

/**
 * Extract a uint32_t from data channel message by name.
 *
 * @param msg The message to extract the data from.
 * @param key The key to extract.
 * @param dst A pointer to an int to place the value in.
 */
process_result_t message_get_int(json_object *msg, const char *key, uint32_t *dst) {
    json_object *tmpJson = NULL;

    if (!json_object_object_get_ex(msg, key, &tmpJson)) {
        LOG_ERROR("Could not read \"%s\" from message.\n", key);
        return PROCESS_FAILURE;
    }

    // Ugh, no way to check there result of this.
    *dst = (uint32_t)json_object_get_int(tmpJson);

    return PROCESS_SUCCESS;
}

/**
 * Extract a uint64_t from data channel message by name.
 *
 * @param msg The message to extract the data from.
 * @param key The key to extract.
 * @param dst A pointer to an int to place the value in.
 */
process_result_t message_get_uint64(json_object *msg, const char *key, uint64_t *dst) {
    
    json_object *tmpJson = NULL;

    if (!json_object_object_get_ex(msg, key, &tmpJson)) {
        LOG_ERROR("Could not read \"%s\" from message.\n", key);
        return PROCESS_FAILURE;
    }

    json_parse_int64(json_object_get_string(tmpJson), (int64_t *)dst);

    return PROCESS_SUCCESS;
}


/**
 * @brief Create an data_message_t* object from a pubnub subscribe response.
 *
 * @param msg The message returned from a pubnub sync.
 * @returns A freshly allocated data_message_t pointer. It is the
 * responsibility of the caller to free.
 */
data_message_t* extract_data_message(json_object *msg) {

    data_message_t *data = calloc(1, sizeof(data_message_t));

    json_object *msgData = json_object_array_get_idx(msg, 0);

    data->result = message_get_int(msgData, "sleep", &data->sleepTime);
    if (data->result != PROCESS_SUCCESS) {
        return data;
    }

    data->result = message_get_uint64(msgData, "UUID", &data->uuid);
    if (data->result != PROCESS_SUCCESS) {
        return data;
    }

    return data;
}

void process_message(struct pubnub *pnCtx, json_object *msg) {

    data_message_t *work = extract_data_message(msg);

    // We are done with this object now.
    json_object_put(msg);

    dispatch_work(work);


}
