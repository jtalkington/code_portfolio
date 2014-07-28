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

#include <check.h>

#include "common.h"

// Ugly, but needed to access the internals.
#include "../src/fifo.c"

START_TEST(test_fq_push) {
    fifo_queue_t *fq = fifo_queue_new();

    fqueue_entry_t *first = calloc(1, sizeof(fqueue_entry_t));
    fqueue_entry_t *second = calloc(1, sizeof(fqueue_entry_t));
    fqueue_entry_t *third = calloc(1, sizeof(fqueue_entry_t));

    fq_push(fq, first);
    ck_assert(first->next == NULL);
    ck_assert(fq->head == first);
    ck_assert(fq->tail == first);

    fq_push(fq, second);
    ck_assert(first->prev == NULL);
    ck_assert(first->next == second);
    ck_assert(second->prev == first);
    ck_assert(second->next == NULL);
    ck_assert(fq->head == first);
    ck_assert(fq->tail == second);

    fq_push(fq, third);
    ck_assert(first->prev == NULL);
    ck_assert(first->next == second);
    ck_assert(second->prev == first);
    ck_assert(second->next == third);
    ck_assert(third->prev == second);
    ck_assert(third->next == NULL);
    ck_assert(fq->head == first);
    ck_assert(fq->tail == third);


    // Each test is run in it's own process, so don't worry about freeing 
    // memory - Yeeehaaw!
} END_TEST;

START_TEST(test_fq_shift) {

    fifo_queue_t *fq = fifo_queue_new();
    
    fqueue_entry_t *first = calloc(1, sizeof(fqueue_entry_t));
    fqueue_entry_t *second = calloc(1, sizeof(fqueue_entry_t));
    fqueue_entry_t *third = calloc(1, sizeof(fqueue_entry_t));

    fq_push(fq, first);
    fq_push(fq, second);
    fq_push(fq, third);

    fqueue_entry_t *entry = fq_shift(fq);
    ck_assert(entry == first);
    ck_assert(fq->head == second);
    ck_assert(fq->tail == third);
    ck_assert(second->prev == NULL);
    ck_assert(second->next == third);
    ck_assert(third->prev == second);
    ck_assert(third->next == NULL);
    ck_assert(entry->prev == NULL);
    ck_assert(entry->next == NULL);

    entry = fq_shift(fq);
    ck_assert(entry == second);
    ck_assert(fq->head == third);
    ck_assert(fq->tail == third);
    ck_assert(third->prev == NULL);
    ck_assert(third->next == NULL);
    ck_assert(entry->prev == NULL);
    ck_assert(entry->next == NULL);

    entry = fq_shift(fq);
    ck_assert(entry == third);
    ck_assert(fq->head == NULL);
    ck_assert(fq->tail == NULL);
    ck_assert(entry->prev == NULL);
    ck_assert(entry->next == NULL);

    ck_assert(fq->head == NULL);
    ck_assert(fq->tail == NULL);

    entry = fq_shift(fq);
    ck_assert(entry == NULL);

} END_TEST;

START_TEST(test_fifo_queue_push) {

    fifo_queue_t *fq = fifo_queue_new();

    const char *data1 = "data1";

    fifo_queue_push(fq, (void *)data1);
    ck_assert(fq->head->data == data1);

    // We already know the fq_push works from above, so testing more than once
    // is just retesting fq_push again.

} END_TEST;

START_TEST(test_fifo_queue_shift) {

    fifo_queue_t *fq = fifo_queue_new();

    const char *data1 = "data1";
    fifo_queue_push(fq, (void *)data1);

    const char *fetchData = (const char *)fifo_queue_shift(fq);

    ck_assert(fetchData == data1);

} END_TEST;

Suite *create_suite() {
    Suite *s = suite_create("test_queue");

    ADD_TEST(test_fq_push);
    ADD_TEST(test_fq_shift);
    ADD_TEST(test_fifo_queue_push);
    ADD_TEST(test_fifo_queue_shift);
    
    
    return s;
}

int main() {
    int failures;

    SRunner *sr = srunner_create(create_suite());

    srunner_run_all(sr, CK_NORMAL);

    failures = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
