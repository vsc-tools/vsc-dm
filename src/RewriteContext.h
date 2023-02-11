/**
 * RewriteContext.h
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
#include "vsc/dm/IRewriteContext.h"
#include "vsc/dm/impl/ContextDelegator.h"
#include "vsc/dm/impl/UP.h"

namespace vsc {
namespace dm {



class RewriteContext :
    public virtual IRewriteContext,
    public virtual ContextDelegator {
public:
    RewriteContext(
        IContext                        *ctxt,
        const std::vector<IAccept *>    &roots);

    virtual ~RewriteContext();

    virtual const std::vector<IAcceptUP> &getRoots() const override;

    virtual void setRoot(int32_t idx, IAccept *r, bool owned) override;

    virtual void addRoot(IAccept *r, bool owned) override;

    virtual void pushContext() override;

    virtual void popContext() override;

    virtual int32_t contextDepth() override;

private:
    using ContextT=std::vector<UP<IAccept>>;
    std::vector<ContextT>                       m_context_s;

};

}
}


