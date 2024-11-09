/**
 * IValOps.h
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
#include "vsc/dm/impl/UP.h"

namespace vsc {
namespace dm {

class IValIterator;
class IValMutIterator;

class ValRef;
class IValOps;
using IValOpsUP=UP<IValOps>;
class IValOps {
public:

    virtual ~IValOps() { }

    virtual void initVal(ValRef &v) = 0;

    virtual void finiVal(ValRef &v) = 0;

    virtual ValRef copyVal(const ValRef &src) = 0;

    virtual IValIterator *mkValIterator(const ValRef &src) = 0;

    virtual IValMutIterator *mkValMutIterator(const ValRef &src) = 0;

};

} /* namespace dm */
} /* namespace vsc */


