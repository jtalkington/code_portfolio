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

#include "../src/data_message.h"
#include "../src/control_message.h"
#include "../src/process.h"
#include "../src/json_misc.h"

#define ADD_TEST(testName) \
{\
    TCase *tc_##testName = tcase_create(#testName); \
    tcase_add_test(tc_##testName, testName); \
    suite_add_tcase(s, tc_##testName); \
}

#define ADD_SUITE(suiteName) \
{\
    Suite *suiteName(void);\
    srunner_add_suite(sr, suiteName());\
}
