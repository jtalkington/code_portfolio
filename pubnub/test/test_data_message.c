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


START_TEST(test_extract_data_message) {

    struct json_object *jsonMsg = json_object_new_object();
    json_object_object_add(jsonMsg, "sleep", json_object_new_int(30));
    json_object_object_add(jsonMsg, "UUID", json_object_new_int64(7));

    data_message_t *dataMsg = extract_data_message(jsonMsg);

    ck_assert(dataMsg != NULL);
    ck_assert(dataMsg->sleepTime == 30);
    ck_assert(dataMsg->uuid == 7);

} END_TEST;

Suite *data_message_proccess_suite() {
    Suite *s = suite_create("data_message_proccess");

    ADD_TEST(test_extract_data_message);
    
    return s;
}
