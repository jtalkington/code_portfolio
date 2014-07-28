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

#include "data_channel.h"
#include "control_channel.h"
#include "publisher.h"

control_message_t* create_control_message(data_message_t *dataMsg) {

    control_message_t *ctrlMsg = calloc(1, sizeof(control_message_t));

    ctrlMsg->result = get_process_result_string(dataMsg->result);
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

    tmpVal = json_object_new_string(msg->result);
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
        return result;
    }

    json_object *msgJson = NULL;
    msgJson = convert_control_message_to_json(msg);

    result = publish_message("control_channel", msgJson);

    json_object_put(msgJson);
    free(msg);

    return result;
}
