/**
 * IValIterator.h
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
#include "vsc/dm/impl/UP.h"
#include "vsc/dm/IDataType.h"

namespace vsc {
namespace dm {

class ValRef;

class IValIterator;
using IValIteratorUP=UP<IValIterator>;
class IValIterator {
public:

    virtual ~IValIterator() { }

    // Resets the iterator to its initial point
    virtual void reset() = 0;

    // Gets the data type of the current value
    virtual IDataType *getDataType() = 0;

    // Gets the value of the current field
    virtual ValRef getVal() = 0;

    // Returns the number of fields in the current scope
    virtual int32_t numFields() = 0;

    virtual IDataType *getFieldType(int32_t f) = 0;

    virtual ValRef getFieldVal(int32_t f) = 0;

    virtual std::string getFieldName(int32_t f) = 0;

    // Pushes into a specific field scope
    virtual bool push(int32_t idx) = 0;

    // Pops out of the current scope
    virtual bool pop() = 0;

};

} /* namespace dm */
} /* namespace vsc */


