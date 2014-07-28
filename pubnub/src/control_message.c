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

#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <json.h>
#include <stdio.h>

#include "config.h"
#include "control_message.h"
#include "message_types.h"
#include "publisher.h"
#include "log.h"
#include "stats.h"
#include "json_misc.h"

control_message_t* create_control_message(data_message_t *dataMsg) {

    control_message_t *ctrlMsg = calloc(1, sizeof(control_message_t));

    ctrlMsg->dataResult = get_process_result_string(dataMsg->result);
    ctrlMsg->uuid = dataMsg->uuid;

    pthread_t tid = pthread_self();
    memcpy(&ctrlMsg->workerId, &tid,
            (sizeof(ctrlMsg->workerId) > sizeof(tid) ? sizeof(tid) : sizeof(ctrlMsg->workerId)));

    return ctrlMsg;
}

json_object *convert_control_message_to_json(control_message_t *msg) {

    json_object *newObj = json_object_new_object();
    json_object *tmpVal = NULL;

    char strVal[64];

    tmpVal = json_object_new_string(msg->dataResult);
    json_object_object_add(newObj, "result", tmpVal);

    sprintf(strVal, "%"PRIu64, msg->uuid);
    tmpVal = json_object_new_string(strVal);
    json_object_object_add(newObj, "UUID", tmpVal);

    sprintf(strVal, "%"PRIu64, msg->workerId);
    tmpVal = json_object_new_string(strVal);
    json_object_object_add(newObj, "workerId", tmpVal);

    return newObj;
}

process_result_t publish_control_message(control_message_t *msg) {

    process_result_t result = publisher_init();
    if (result != PROCESS_SUCCESS) {
        message_count_increment(COUNTER_CONTROL_SENT_ERROR);
        return result;
    }

    json_object *msgJson = NULL;
    msgJson = convert_control_message_to_json(msg);

    result = publish_message(PUBNUB_MESSAGE_CHANNEL, MESSAGE_TYPE_CONTROL, msgJson);
        
    message_count_increment(COUNTER_CONTROL_SENT);

    // XXX:jlt Disable this for now to diagnose crashes in json-c.
    //json_object_put(msgJson);
    free(msg);

    return result;
}

/**
 * @brief Create an control_message_t* object from a pubnub subscribe response.
 *
 * @param msg The message returned from a pubnub sync.
 * @returns A freshly allocated control_message_t pointer or NULL. It is the
 * responsibility of the caller to free. If there is anything wrong with the
 * message it is completely discarded, and NULL is returned.
 */
control_message_t* extract_control_message(json_object *msg) {

    control_message_t *data = calloc(1, sizeof(control_message_t));

    data->result = json_get_uint64(msg, "workerId", &data->workerId);
    if (data->result != PROCESS_SUCCESS) {
        LOG_ERROR("Could not extract \"workerId\" from data message.");
        free(data);
        return NULL;
    }

    data->result = json_get_uint64(msg, "UUID", &data->uuid);
    if (data->result != PROCESS_SUCCESS) {
        LOG_ERROR("Could not extract \"UUID\" from data message.");
        free(data);
        return NULL;
    }

    data->dataResult = json_get_string(msg, "result");
    if (data->dataResult == NULL) {
        free(data);
        return NULL;
    }

    return data;
}

void process_control_message_json(json_object *msg) {

    control_message_t *work = extract_control_message(msg);

    if (work == NULL) {
        message_count_increment(COUNTER_CONTROL_ERROR);
        return;
    }

    LOG_DEBUG("Successfully processed control message for data message %" PRIu64 ": Result = %s.",
                work->uuid, work->dataResult);

    message_count_increment(COUNTER_CONTROL_SUCCESS);

    print_stats();

    free(work);
}
