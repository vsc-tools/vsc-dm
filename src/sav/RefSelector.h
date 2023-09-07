/**
 * RefSelector.h
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
#include <vector>
#include "vsc/dm/IContext.h"
#include "vsc/dm/IRefSelector.h"
#include "vsc/dm/IModelFieldRef.h"

namespace vsc {
namespace dm {


class RefSelector : public virtual IRefSelector {
public:
    RefSelector(
        IContext                            *ctxt,
        IModelFieldRef                      *ref,
        const std::vector<IModelField *>    &candidates);

    virtual ~RefSelector();

    virtual IModelFieldRef *getRef() const override { return m_ref; }

    virtual const std::vector<IModelField *> getCandidates() const override {
        return *m_candidates;
    }

    virtual void init(IContext *ctxt) override;

    virtual int32_t getSelectorBits() const override { return m_sel_bits; }

    virtual IModelField *getSelector() const override { return m_selector.get(); }

    virtual IModelConstraint *getValidC() const override { return m_valid_c.get(); }

    virtual IModelConstraint *getValidSoftC() const override { return m_valid_soft_c.get(); }

    virtual void addIncludeRange(int32_t l, int32_t h, IModelExpr *cond) override;

private:
    static dmgr::IDebug                     *m_dbg;

    struct IncRange {
        int32_t             l;
        int32_t             h;
        IModelExprUP        c;
    };
    IModelFieldRef                          *m_ref;
    const std::vector<IModelField *>        *m_candidates;
    IModelFieldUP                           m_selector;
    int32_t                                 m_sel_bits;
    IModelConstraintUP                      m_valid_c;
    IModelConstraintUP                      m_valid_soft_c;
    std::vector<IncRange>                   m_inc_ranges;
};

}
}


