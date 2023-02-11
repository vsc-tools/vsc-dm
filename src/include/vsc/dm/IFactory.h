/**
 * IFactory.h
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
#include "dmgr/IDebugMgr.h"
#include "vsc/dm/IContext.h"
#include "vsc/dm/IRewriteContext.h"

namespace vsc {
namespace dm {

class IFactory {
public:

    virtual ~IFactory() { }

    virtual void init(dmgr::IDebugMgr *dm) = 0;

    virtual dmgr::IDebugMgr *getDebugMgr() const = 0;

    virtual IContext *mkContext() = 0;

    virtual IRewriteContext *mkRewriteContext(
        IContext                        *ctx,
        const std::vector<IAccept *>    &roots) = 0;

};


}
}
