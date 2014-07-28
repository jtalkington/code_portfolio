/*
# Copyright 2014 Jerry Talkington
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#  http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#*/

#ifndef __log_h_
#define __log_h_

#include <stdio.h>
#include "config.h"

#ifdef ENABLE_DEBUG
# define LOG_DEBUG(format, ...) printf("%s %i: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

# define LOG_ERROR(format, ...) printf("%s %i: " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif //__log_h_
