/**
 * ValMutIteratorDefault.h
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
#include "vsc/dm/IValMutIterator.h"
#include "ValIteratorDefault.h"

namespace vsc {
namespace dm {



class ValMutIteratorDefault :
    public virtual IValMutIterator,
    public virtual ValIteratorDefault {
public:
    ValMutIteratorDefault(const ValRef &src);

    virtual ~ValMutIteratorDefault();

    // Gets the value of the current field
    virtual void setVal(const ValRef &v) override;

    virtual void setFieldVal(int32_t f, const ValRef &v) override;

};

}
}


