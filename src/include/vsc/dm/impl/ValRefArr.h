/**
 * ValRefArr.h
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
#include "vsc/dm/IDataTypeArray.h"
#include "vsc/dm/impl/ValRef.h"

namespace vsc {
namespace dm {



class ValRefArr : public ValRef {
public:

    ValRefArr() {}

    ValRefArr(const ValRef &rhs) : ValRef(rhs) { }

    virtual ~ValRefArr() { }

    int32_t getSize() const {
        return dynamic_cast<IDataTypeArray *>(type())->getSize();
    }

};

} /* namespace dm */
} /* namespace vsc */


