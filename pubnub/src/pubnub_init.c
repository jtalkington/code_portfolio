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

#include <stdbool.h>
#include <pubnub.h>
#include <pubnub-sync.h>

#include "config.h"
#include "process.h"

process_result_t init_pubnub_sync_context(struct pubnub **pnPtr, struct pubnub_sync **syncPtr) {

    if ((*syncPtr) == NULL) {
        (*syncPtr) = pubnub_sync_init();

        if ((*syncPtr) == NULL) {
            return PROCESS_INIT_SYNC_FAIL;
        }
    }

    if ((*pnPtr) == NULL) {
        (*pnPtr) = pubnub_init(PUBNUB_PUBLISH_KEY, PUBNUB_SUBSCRIBE_KEY,
                            &pubnub_sync_callbacks, (*syncPtr));

        if ((*pnPtr) == NULL) {
            return PROCESS_INIT_PN_FAIL;
        }
    }

    return PROCESS_SUCCESS;
}
