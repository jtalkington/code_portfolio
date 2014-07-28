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

#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h>

#include "config.h"
#include "listener.h"
#include "worker.h"

int main() {

    // must be done before threads are created
    curl_global_init(CURL_GLOBAL_ALL);

    listener_init();
    init_workers();

    return listener_loop(PUBNUB_MESSAGE_CHANNEL);

}
