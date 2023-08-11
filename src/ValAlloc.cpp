/*
 * ValAlloc.cpp
 *
 * Copyright 2023 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author:
 */
#include <stdio.h>
#include "ValAlloc.h"


namespace vsc {
namespace dm {


ValAlloc::ValAlloc() {

}

ValAlloc::~ValAlloc() {

}

Val *ValAlloc::alloc(uint32_t n_bytes) {
    uint32_t arr_sz = ((n_bytes-1)/sizeof(uintptr_t))+1;
    uint32_t total_sz = sizeof(Val)+(sizeof(uintptr_t)*(arr_sz-1));
    fprintf(stdout, "sizeof(Val): %d n_bytes: %d arr_sz=%d total_sz: %d\n", sizeof(Val), n_bytes, arr_sz, total_sz);
    Val *v = reinterpret_cast<Val *>(::operator new(total_sz));
    v->sz = arr_sz*sizeof(uintptr_t);
    return v;
}

void ValAlloc::free(Val *v) {

}

}
}
