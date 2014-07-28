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

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "stats.h"
#include "log.h"

static stats_t sg_StatCounter = {
    .dataSuccess = 0,
    .dataError = 0,
    .controlSuccess = 0,
    .controlError = 0,
    .controlSent = 0,
    .controlSentError = 0,
    .unknownError = 0,
    .messageReceived = 0
};

void message_count_increment(stats_type_t type) {

    /// @TODO Lock when PTHREAD_IMPLEMENT
    
    switch (type) {
        case COUNTER_DATA_SUCCESS:
            {
                sg_StatCounter.dataSuccess++;
            } break;
        case COUNTER_DATA_ERROR:
            {
                sg_StatCounter.dataError++;
            } break;
        case COUNTER_CONTROL_SUCCESS:
            {
                sg_StatCounter.controlSuccess++;
            } break;
        case COUNTER_CONTROL_ERROR:
            {
                sg_StatCounter.controlError++;
            } break;
        case COUNTER_CONTROL_SENT:
            {
                sg_StatCounter.controlSent++;
            } break;
        case COUNTER_CONTROL_SENT_ERROR:
            {
                sg_StatCounter.controlSentError++;
            } break;
        case COUNTER_UNKOWN_ERROR:
            {
                sg_StatCounter.unknownError++;
            } break;
        case COUNTER_MESSAGE_RECEIVED:
            {
                sg_StatCounter.messageReceived++;
            } break;
        default:
            {
                LOG_ERROR("Could not determine message type for %i", type);
            } break;
    }
}

void get_message_stats(stats_t *outCounter) {
    /// @TODO Lock when PTHREAD_IMPLEMENT

    memcpy(outCounter, &sg_StatCounter, sizeof(sg_StatCounter));

}

char *get_message_stats_string() {

    stats_t stats;
    get_message_stats(&stats);

    const char *format = "Message Statistics\n"
                          "  Data Messages\n"
                          "    Successful:     %"PRIu64"\n"
                          "    Unsuccessful:   %"PRIu64"\n"
                          "  Control Messages\n"
                          "    Successful:     %"PRIu64"\n"
                          "    Unsuccessful:   %"PRIu64"\n"
                          "    Sent:           %"PRIu64"\n"
                          "    Send Failures:  %"PRIu64"\n"
                          "  Other\n"
                          "    Unknown Errors: %"PRIu64"\n"
                          "    Total Received: %"PRIu64"\n";

    size_t responseSize = strlen(format) + (21 * MESSAGE_COUNTER_ELEMENTS);
    char *response = calloc(1, responseSize);

    if (snprintf(response, responseSize, format,
                        stats.dataSuccess,
                        stats.dataError,
                        stats.controlSuccess,
                        stats.controlError,
                        stats.controlSent,
                        stats.controlSentError,
                        stats.unknownError,
                        stats.messageReceived) == 0) {
        free(response);
        response = NULL;
    }

    return response;

}

void print_stats() {
    char *statsString = get_message_stats_string();

    if(statsString == NULL) {
        LOG_ERROR("Could not get the message stats.");
        return;
    }

    printf("%s", statsString);

    free(statsString);
}
