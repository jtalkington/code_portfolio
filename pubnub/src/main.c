#include <stdlib.h>
#include <curl/curl.h>

#include "config.h"

int main() {

    // must be done before threads are created
    curl_global_init(CURL_GLOBAL_ALL);

}
