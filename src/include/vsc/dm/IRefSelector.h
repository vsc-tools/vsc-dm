/**
 * IRefSelector.h
 *
 * Copyright 2022 Matthew Ballance and Contributors
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
#include <memory>
#include <vector>
#include "vsc/dm/IModelExpr.h"
#include "vsc/dm/IModelFieldRef.h"

namespace vsc {
namespace dm {

class IContext;

class IRefSelector;
using IRefSelectorUP=UP<IRefSelector>;
class IRefSelector {
public:

    virtual ~IRefSelector() { }

    virtual IModelFieldRef *getRef() const = 0;

    virtual const std::vector<IModelField *> getCandidates() const = 0;

    virtual void init(IContext *ctxt) = 0;

    virtual int32_t getSelectorBits() const = 0;

    virtual IModelField *getSelector() const = 0;

    virtual IModelConstraint *getValidC() const = 0;

    virtual IModelConstraint *getValidSoftC() const = 0;

    virtual void addIncludeRange(int32_t l, int32_t h, IModelExpr *cond) = 0;

};

}
}

