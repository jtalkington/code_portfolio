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
#include "fifo.h"

typedef struct fqueue_entry_t {
    struct fqueue_entry_t *next;
    struct fqueue_entry_t *prev;
    void *data;
} fqueue_entry_t;

struct fifo_queue_t {
    fqueue_entry_t *head;
    fqueue_entry_t *tail;
};

fifo_queue_t *fifo_queue_new() {
    fifo_queue_t *newQueue = calloc(1, sizeof(fifo_queue_t));

    return newQueue;
}

/**
 * @brief Insert an entry to the queue;
 * 
 * @param queue The queue to insert into.
 * @param entry The entry to insert.
 */
void fq_push(fifo_queue_t *queue, fqueue_entry_t *entry) {

    if (queue == NULL) {
        return;
    }

    if (queue->head == NULL) {
        queue->head = entry;
        queue->tail = entry;
        return;
    }

    fqueue_entry_t *left = queue->tail;
    left->next = entry;
    entry->prev = left;
    queue->tail = entry;
}

void fifo_queue_push(fifo_queue_t *queue, void *data) {

    if (queue == NULL) {
        return;
    }

    fqueue_entry_t *entry = calloc(1, sizeof(fqueue_entry_t));

    entry->data = data;

    fq_push(queue, entry);
}

/**
 * @brief Pulls the first entry from a fifo_queue
 *
 * @param queue The queue to pull from.
 */
fqueue_entry_t *fq_shift(fifo_queue_t *queue) {

    if (queue == NULL) {
        return NULL;
    }

    fqueue_entry_t *entry = queue->head;

    if (entry == NULL) {
        return entry;
    }

    queue->head = entry->next;
    
    if (queue->head != NULL) {
        queue->head->prev = NULL;
    } else {
        queue->tail = NULL;
    }

    // This is no longer in the queue, remove references.
    entry->prev = NULL;
    entry->next = NULL;
    
    return entry;
}

void *fifo_queue_shift(fifo_queue_t *queue) {

    if (queue == NULL) {
        return NULL;
    }

    fqueue_entry_t *entry = fq_shift(queue);

    if (entry == NULL) {
        return entry;
    }

    void *data = entry->data;

    free(entry);

    return data;
}

