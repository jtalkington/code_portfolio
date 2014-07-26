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
#include <pubnub.h>
#include <pubnub-sync.h>
#include <stdbool.h>
#include <stdio.h>

#include "config.h"
#include "process.h"
#include "log.h"
#include "pubnub_init.h"

// These are static to keep the publish/subscribe contexts separate.

/// The sync context.
static struct pubnub_sync *sg_Sync = NULL;
/// The subscribe context.
static struct pubnub *sg_Pn = NULL;

extern bool g_Shutdown;

/**
 * @brief Initialize the subscriber context.
 * @returns False on success, True if the context was already initialized.
 */
bool listener_init() {

    return init_pubnub_sync_context(&sg_Pn, &sg_Sync);

}

/**
 * @brief Pull the messages from sync queue and send them to the processor.
 * @returns Any error messages returned by pubnub.
 */
int listener_loop(const char *channel) {

    // It's ok if this fails, since it may have already been initialized. Check
    // return value to avoid compiler warning.
    if (listener_init()) {};

    do {
        pubnub_subscribe(sg_Pn, channel, -1, NULL, NULL);

        enum pubnub_res retVal = pubnub_sync_last_result(sg_Sync);

        if (retVal != PNR_OK) {
            return retVal;
        }

        struct json_object *msg = pubnub_sync_last_response(sg_Sync);

#ifdef ENABLE_DEBUG
        int len = json_object_array_length(msg);
        for (int i = 0; i < len; i++) {
            json_object *obj = json_object_array_get_idx(msg, i);
            LOG_DEBUG("received: %s\n", json_object_get_string(obj));
        }
#endif
        
        process_message(sg_Pn, msg);
    
    } while (g_Shutdown == false);

    // This should never be reached, but avoid a compiler warning.
    return PNR_CANCELLED;
}

