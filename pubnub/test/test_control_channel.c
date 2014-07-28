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
#include <json.h>

#include "common.h"

START_TEST(test_create_control_message) {

    data_message_t dataMsg;
    dataMsg.uuid = 7;
    dataMsg.sleepTime = 0;
    dataMsg.result = PROCESS_FAILURE;

    control_message_t *ctrlMsg = create_control_message(&dataMsg);

    ck_assert(ctrlMsg->uuid == dataMsg.uuid);
    ck_assert(strcmp(ctrlMsg->result, get_process_result_string(dataMsg.result)) == 0);

} END_TEST;

START_TEST(test_convert_control_message_to_json) {

    control_message_t ctrlMsg;
    ctrlMsg.result = "success";
    ctrlMsg.uuid = 7;
    ctrlMsg.workerId = 5;

    json_object *jsonMsg = convert_control_message_to_json(&ctrlMsg);

    int i = 0;

    { // keep the definitions in the foreach macro from polluting the scope
        json_object_object_foreach(jsonMsg, key, val) {
            i++;
        }
    }

    ck_assert_msg(i == 3, "Expected i to be 3, was %i.\n", i);

    process_result_t result = PROCESS_SUCCESS;
    uint64_t uuid;

    result = json_get_uint64(jsonMsg, "UUID", &uuid);
    ck_assert(result == PROCESS_SUCCESS);
    ck_assert(uuid == ctrlMsg.uuid);

    result = json_get_uint64(jsonMsg, "workerId", &uuid);
    ck_assert(result == PROCESS_SUCCESS);
    ck_assert(uuid == ctrlMsg.workerId);

    const char *resultString = json_get_string(jsonMsg, "result");
    ck_assert(resultString != NULL);
    ck_assert(strcmp(resultString, ctrlMsg.result) == 0);


} END_TEST;

Suite *control_channel_suite() {
    Suite *s = suite_create("control_channel");

    ADD_TEST(test_create_control_message);
    ADD_TEST(test_convert_control_message_to_json);
    
    return s;
}
