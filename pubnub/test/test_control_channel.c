 /*
# * Copyright 2014 Jerry Talkington
# *  
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# * http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# */

#include <check.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"

bool g_Shutdown = false;

START_TEST(test_create_control_message) {

    data_message_t dataMsg;
    dataMsg.uuid = 7;
    dataMsg.sleepTime = 0;
    dataMsg.result = PROCESS_FAILURE;

    control_message_t *ctrlMsg = create_control_message(&dataMsg);

    ck_assert(ctrlMsg->uuid == dataMsg.uuid);
    ck_assert(strcmp(ctrlMsg->result, get_process_result_string(dataMsg.result)) == 0);

} END_TEST;


Suite *create_suite() {
    Suite *s = suite_create("Unit Tests");

    ADD_TEST(test_create_control_message);
    
    return s;
}
