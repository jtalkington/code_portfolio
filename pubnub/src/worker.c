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
#include <unistd.h>

#include "worker.h"
#include "log.h"
#include "control_message.h"
#include "data_message.h"
#include "fifo.h"
#include "json_misc.h"

static fifo_queue_t *sg_WorkQueue = NULL;

/**
 * @brief Finish processing a data_message_t object and free it.
 * 
 * @param work The object to finish processing on.
 * @param result The process_result_t result.
 */
/**
 * Rip a message from the queue and process it. One day this will be from a
 * thread pool.
 */
void worker_thread_work() {
    json_object *pnMsg = (json_object *)fifo_queue_shift(sg_WorkQueue);

    // The message comes as a one element array.
    json_object *msgData = json_object_array_get_idx(pnMsg, 0);

    json_object *msg;
    json_object_object_get_ex(msgData, "data", &msg);

    message_type_t type;
    json_get_int(msgData, "messageType", &type);

    switch (type) {
        case MESSAGE_TYPE_DATA: 
            {
                process_data_message_json(msg);
            } break;
        case MESSAGE_TYPE_CONTROL:
            {
                process_control_message_json(msg);
            } break;
        default:
            break;
    }

    json_object_put(msg);
    json_object_put(msgData);
    json_object_put(pnMsg);
}

void dispatch_work(json_object *msg) {

    fifo_queue_push(sg_WorkQueue, msg);
    worker_thread_work();
}

void init_workers() {
    if (sg_WorkQueue != NULL) {
        return;
    }
    
    sg_WorkQueue = fifo_queue_new();
}
