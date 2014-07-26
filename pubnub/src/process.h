#ifndef __process_h_
#define __process_h_

#include <pubnub.h>
#include <json.h>

/**
 * @brief The possible results of processing the message.
 */
typedef enum process_result_t {
    PROCESS_SUCCESS = 0,
    PROCESS_FAILURE
} process_result_t;

/**
 * @brief Convert a process_result_t into a meaningful message.
 *
 * @param result The process_result_t to convert.
 * @returns A human readable const char * explanation.
 */
const char *get_process_result_string(process_result_t result);

/**
 * @brief Process a response from a sync subscribe request.
 *
 * @param pnCtx The PubNub context.
 * @param msg The sync response.
 *
 * @TODO Convert this into a callback that is set when the listener_loop() is
 * called.
 */
void process_message(struct pubnub *pnCtx, json_object *msg);

#endif // __process_h_
