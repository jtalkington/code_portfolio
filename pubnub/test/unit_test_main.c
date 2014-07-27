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
#include <check.h>

Suite *create_suite(void);

int main() {
    int failures;

    Suite *s = create_suite();
    SRunner *sr = srunner_create (s);
    srunner_run_all (sr, CK_NORMAL);

    failures = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

