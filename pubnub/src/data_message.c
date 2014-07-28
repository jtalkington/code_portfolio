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
#include <unistd.h>

#include "data_message.h"
#include "control_message.h"
#include "process.h"
#include "log.h"
#include "worker.h"
#include "json_misc.h"
#include "stats.h"

/**
 * @brief Create an data_message_t* object from a pubnub subscribe response.
 *
 * @param msg The message returned from a pubnub sync.
 * @returns A freshly allocated data_message_t pointer or NULL. It is the
 * responsibility of the caller to free. If there is anything wrong with the
 * message it is completely discarded, and NULL is returned.
 */
data_message_t* extract_data_message(json_object *msg) {

#ifdef ENABLE_DEBUG
        int len = json_object_array_length(msg);
        for (int i = 0; i < len; i++) {
            json_object *obj = json_object_array_get_idx(msg, i);
            LOG_DEBUG("received: %s\n", json_object_get_string(obj));
        }
#endif

    data_message_t *data = calloc(1, sizeof(data_message_t));

    data->result = json_get_int(msg, "sleep", &data->sleepTime);
    if (data->result != PROCESS_SUCCESS) {
        LOG_ERROR("Could not extract \"sleep\" from data message");
        free(data);
        return NULL;
    }

    data->result = json_get_uint64(msg, "UUID", &data->uuid);
    if (data->result != PROCESS_SUCCESS) {
        LOG_ERROR("Could not extract \"UUID\" from data message");
        free(data);
        return NULL;
    }

    return data;
}

/**
 * Send a control message acknowledment and free up the work.
 *
 * @param work The message that was worked on.
 */
static void finish_data_message_work(data_message_t *work) {

    control_message_t *ctrlMsg = create_control_message(work);

    if (work->result == PROCESS_SUCCESS) {
        LOG_DEBUG("Created control channel object: %"PRIu64", %"PRIu64", %s.\n",
            ctrlMsg->workerId, ctrlMsg->uuid, ctrlMsg->dataResult);

        publish_control_message(ctrlMsg);
        message_count_increment(COUNTER_DATA_SUCCESS);
    } else {
        message_count_increment(COUNTER_DATA_ERROR);
    }

    print_stats();

    free(work);
}

void process_data_message_json(json_object *msg) {

    data_message_t *work = extract_data_message(msg);

    if (work == NULL) {
        message_count_increment(COUNTER_DATA_ERROR);
        return;
    }

    // Only continue processing if successful.
    if (work->result == PROCESS_SUCCESS) {
        LOG_DEBUG("Sleeping %i seconds...\n", work->sleepTime);
        sleep(work->sleepTime);
    }

    finish_data_message_work(work);
}

