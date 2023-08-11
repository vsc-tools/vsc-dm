/**
 * Val.h
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
#pragma once
#include <stdint.h>

namespace vsc {
namespace dm {

class IContext;


struct Val {
    union {
        IContext    *cp;
        Val         *np;
    } p;
    uint32_t    sz;
    uintptr_t   val[1];

    static inline uintptr_t Val2ValPtr(Val *v) {
        return reinterpret_cast<uintptr_t>(v->val);
    }

    static Val *ValPtr2Val(uintptr_t vp) {
        Val *v = 0;
        return reinterpret_cast<Val *>(vp - reinterpret_cast<uintptr_t>(v->val));
    }
};

struct ValDataStr {
    uint32_t            sz;
    char                str[1];
};

struct ValDataVec {
    uint32_t            sz;
    uintptr_t           data[1];
};

struct ValDataPtr {
    uintptr_t           prev;
    uintptr_t           next;
    uintptr_t           ref;
};

} /* namespace dm */
} /* namespace vsc */


