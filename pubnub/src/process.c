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

#include "process.h"

const char *get_process_result_string(process_result_t result) {

    switch(result) {
        case PROCESS_SUCCESS:
            {
                return "success";
            } break;
        case PROCESS_FAILURE:
            {
                return "failure";
            } break;
        case PROCESS_PN_SUBSCRIBE_FAIL:
            {
                return "PubNub subscribe failure";
            } break;
        case PROCESS_INIT_SYNC_FAIL:
            {
                return "PubNub sync init failure";
            } break;
        case PROCESS_INIT_PN_FAIL:
            {
                return "PubNub context init failure";
            } break;
        case PROCESS_PUBLISH_FAIL:
            {
                return "PubNub publish failure";
            } break;
        default:
            break;
    }

    return "unkown";
}

