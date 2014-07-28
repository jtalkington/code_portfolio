#ifndef __process_h_
#define __process_h_

#include <pubnub.h>
#include <json.h>

/**
 * @brief The possible results of processing the message.
 */
typedef enum process_result_t {
    PROCESS_SUCCESS = 0,
    PROCESS_FAILURE,
    PROCESS_PN_SUBSCRIBE_FAIL,
    PROCESS_INIT_SYNC_FAIL,
    PROCESS_INIT_PN_FAIL,
    PROCESS_PUBLISH_FAIL
} process_result_t;

/**
 * @brief Convert a process_result_t into a meaningful message.
 *
 * @param result The process_result_t to convert.
 * @returns A human readable const char * explanation.
 */
const char *get_process_result_string(process_result_t result);

#endif // __process_h_
