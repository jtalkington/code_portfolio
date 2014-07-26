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

#include "data_channel_worker.h"
#include "log.h"
#include "control_channel.h"


/**
 * @brief Finish processing a data_message_t object and free it.
 * 
 * @param work The object to finish processing on.
 * @param result The process_result_t result.
 */
void finish_work(data_message_t *work) {

    control_message_t *ctrlMsg = create_control_message(work);

    LOG_DEBUG("Created control channel object: %llu, %llu, %s.\n",
            ctrlMsg->workerId, ctrlMsg->uuid, ctrlMsg->result);

    free(work);
}

void dispatch_work(data_message_t *work) {

    // There was a parsing failure, just bail.
    if (work->result != PROCESS_SUCCESS) {
        finish_work(work);
        return;
    }

    LOG_DEBUG("Sleeping %i seconds...\n", work->sleepTime);
    sleep(work->sleepTime);

    finish_work(work);
}

