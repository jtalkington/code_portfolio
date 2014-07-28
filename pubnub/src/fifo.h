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

#ifndef __fifo_h_
#define __fifo_h_

#include <stdbool.h>

struct fifo_queue_t;
typedef struct fifo_queue_t fifo_queue_t;

/**
 * @brief Initialize a new fifo_queue.
 *
 * @returns A newly allocated fifo_queue, or NULL if there was a memory failure.
 */
fifo_queue_t *fifo_queue_new();

/**
 * @brief Insert a data object onto the queue.
 *
 * @param queue The queue to insert the object on.
 * @param data The data to insert.
 */
void fifo_queue_push(fifo_queue_t *queue, void *data);
#define fifo_queue_insert fifo_queue_push

/**
 * @brief Pull the first entry from the queue.
 *
 * @param queue The queue to extract the object from.
 */
void *fifo_queue_shift(fifo_queue_t *queue);
#define fifo_queue_next fifo_queue_shift

#endif //__fifo_h_
