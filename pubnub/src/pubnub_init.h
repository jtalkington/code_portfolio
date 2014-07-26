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
#ifndef __pubnub_init_h_
#define __pubnub_init_h_

#include <stdbool.h>
#include <pubnub.h>
#include <pubnub-sync.h>

/**
 * @brief Initialize a pubnub context and sync handler.
 *
 * @param pnPtr A pointer to pubnub pointer.
 * @param syncPtr A pointer to pubnub_sync pointer.
 *
 */
bool init_pubnub_sync_context(struct pubnub **pnPtr, struct pubnub_sync **syncPtr);

#endif // __pubnub_init_h_
