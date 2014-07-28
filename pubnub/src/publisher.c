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

#include <json.h>
#include <pubnub.h>

#include "publisher.h"
#include "pubnub_init.h"

/// The sync context.
static struct pubnub_sync *sg_Sync = NULL;
/// The pubnub context.
static struct pubnub *sg_Pn = NULL;

process_result_t publisher_init() {
    return init_pubnub_sync_context(&sg_Pn, &sg_Sync);
}

process_result_t publish_message(const char *channel, message_type_t msgType, json_object *msg) {

    process_result_t result = PROCESS_SUCCESS; 

    json_object *msgObj = json_object_new_object();
    json_object_object_add(msgObj, "messageType", json_object_new_int(msgType));
    json_object_object_add(msgObj, "data", msg);

    pubnub_publish(sg_Pn, channel, msgObj, -1, NULL, NULL);

    if (pubnub_sync_last_result(sg_Sync) != PNR_OK) {
        result = PROCESS_PUBLISH_FAIL;
    }

    json_object_put(msgObj);
    return PROCESS_SUCCESS;
}
