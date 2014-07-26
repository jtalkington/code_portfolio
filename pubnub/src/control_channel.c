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

#include "data_channel.h"
#include "control_channel.h"

control_message_t* create_control_message(data_message_t *dataMsg) {

    control_message_t *ctrlMsg = calloc(1, sizeof(control_message_t));

    ctrlMsg->result = get_process_result_string(dataMsg->result);
    ctrlMsg->uuid = dataMsg->uuid;

    pthread_t tid = pthread_self();
    memcpy(&ctrlMsg->workerId, &tid,
            (sizeof(ctrlMsg->workerId) > sizeof(tid) ? sizeof(tid) : sizeof(ctrlMsg->workerId)));

    return ctrlMsg;
}

    
