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

#include <stdint.h>

/**
 * The message counter struct.
 */
typedef struct stats_t {
    uint64_t dataSuccess;
    uint64_t dataError;
    uint64_t controlSuccess;
    uint64_t controlError;
    uint64_t controlSent;
    uint64_t controlSentError;
    uint64_t unknownError;
    uint64_t messageReceived;
} stats_t;

/** 
 * @TODO Make this an array of elements with a textual representation, e.g.
 * struct stats[stats_type_t STAT_DATA_SUCCESS] = [uint64_t counter]["This the format text"];
 * and increment the counters in array. Right now adding an element happens in
 * too many places and is very error prone, switching will only require updating
 * stats_type_t and the stats array.
 */
/// The number of elements in the message counter object.
#define MESSAGE_COUNTER_ELEMENTS 8

/**
 * The message type counters. These don't need specific values.
 */
typedef enum stats_type_t {
    COUNTER_DATA_SUCCESS,
    COUNTER_DATA_ERROR,
    COUNTER_CONTROL_SUCCESS,
    COUNTER_CONTROL_ERROR,
    COUNTER_CONTROL_SENT,
    COUNTER_CONTROL_SENT_ERROR,
    COUNTER_UNKOWN_ERROR,
    COUNTER_MESSAGE_RECEIVED
} stats_type_t;

/**
 * Increment the counter for the number of data messages seen.
 *
 * @param type The type of message that was processed.
 */
void message_count_increment(stats_type_t type);

/**
 * Get the current message counter stats.
 *
 * @param outCounter A pointer to a stats_t that can be filled with the
 * current stats.
 */
void get_message_stats(stats_t *outCounter);

/**
 * Get a string representation of the current stats.
 *
 * @returns A char * string of the current stats. The caller is responsible for
 * releasing the memory.
 */
char *get_message_stats_string(void);

/**
 * Print out the stats.
 */

void print_stats(void);
