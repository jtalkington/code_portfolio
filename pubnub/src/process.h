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
 * @brief Process a response from a sync subscribe request.
 *
 * @param pnCtx The PubNub context.
 * @param msg The sync response.
 */
void process_message(struct pubnub *pnCtx, json_object *msg);

#endif // __process_h_
