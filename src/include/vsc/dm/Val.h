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

class IValAlloc;
class ValRef;

using ValData=uintptr_t;

struct Val {
    union {
        IValAlloc   *ap;
        Val         *np;
    } p;
    ValRef      *owner;
    uint32_t    sz;
    ValData     val[1];

    static inline ValData Val2ValPtr(Val *v) {
        return reinterpret_cast<ValData>(v->val);
    }

    static Val *ValPtr2Val(ValData vp) {
        Val *v = 0;
        return reinterpret_cast<Val *>(vp - reinterpret_cast<ValData>(v->val));
    }
};

struct ValDataStr {
    uint32_t            sz;
    char                str[1];
};

struct ValDataVec {
    uint32_t            sz;
    ValData             data[1];
};

struct ValDataPtr {
    uintptr_t           prev;
    uintptr_t           next;
    uintptr_t           ref;
};

} /* namespace dm */
} /* namespace vsc */


