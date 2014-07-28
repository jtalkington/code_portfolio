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

#include "data_channel_process.h"
#include "process.h"
#include "log.h"
#include "data_channel_worker.h"
#include "json_misc.h"

/**
 * @brief Create an data_message_t* object from a pubnub subscribe response.
 *
 * @param msg The message returned from a pubnub sync.
 * @returns A freshly allocated data_message_t pointer or NULL. It is the
 * responsibility of the caller to free. If there is anything wrong with the
 * message it is completely discarded, and NULL is returned.
 */
data_message_t* extract_data_message(json_object *msg) {

    data_message_t *data = calloc(1, sizeof(data_message_t));

    data->result = json_get_int(msg, "sleep", &data->sleepTime);
    if (data->result != PROCESS_SUCCESS) {
        free(data);
        return NULL;
    }

    data->result = json_get_uint64(msg, "UUID", &data->uuid);
    if (data->result != PROCESS_SUCCESS) {
        free(data);
        return NULL;
    }

    return data;
}

void process_message(struct pubnub *pnCtx, json_object *msg) {

    // Extract the message from the array.  The PubNub library already removes
    // the time_token and channel lists from the array, so it ends up being a
    // one object array.
    json_object *msgData = json_object_array_get_idx(msg, 0);
    
    data_message_t *work = extract_data_message(msgData);

    // We are done with this object now.
    json_object_put(msg);

    dispatch_work(work);


}
