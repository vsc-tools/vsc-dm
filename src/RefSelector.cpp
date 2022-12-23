/*
 * RefSelector.cpp
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
#include <algorithm>
#include "vsc/dm/IContext.h"
#include "dmgr/impl/DebugMacros.h"
#include "RefSelector.h"


namespace vsc {
namespace dm {


RefSelector::RefSelector(
    IContext                                *ctxt,
    IModelFieldRef                          *ref,
    const std::vector<IModelField *>        &candidates) 
        : m_ref(ref), m_candidates(&candidates), m_sel_bits(-1) {

    DEBUG_INIT("RefSelector", ctxt->getDebugMgr());

    std::string name = ref->name();
    name += ".selector";

    // Use a placeholder type for now
    IDataTypeInt *selector_t = ctxt->findDataTypeInt(true, 16);
    if (!selector_t) {
        selector_t = ctxt->mkDataTypeInt(true, 16);
        ctxt->addDataTypeInt(selector_t);
    }

    m_selector = IModelFieldUP(
        ctxt->mkModelFieldRoot(selector_t, name));
}

RefSelector::~RefSelector() {

}

void RefSelector::init(IContext *ctxt) {
    DEBUG_ENTER("init %s", m_selector->name().c_str());
    int32_t bits = 0, value = m_candidates->size();

    // Determine how many bits are needed
    do {
        bits++;
        value >>= 1;
    } while (value);

    // Add an extra bit for the sign bit
    bits++;

    m_sel_bits = bits;

    IDataTypeInt *selector_t = ctxt->findDataTypeInt(true, bits);
    if (!selector_t) {
        selector_t = ctxt->mkDataTypeInt(true, bits);
        ctxt->addDataTypeInt(selector_t);
    }

    m_selector->setDataType(selector_t);

    // Add a constraint on the value range
    IModelValUP tmp_v1 = IModelValUP(ctxt->mkModelVal());
    IModelValUP tmp_v2 = IModelValUP(ctxt->mkModelVal());

    tmp_v1->setBits(bits);
    tmp_v2->setBits(bits);

    if (m_inc_ranges.size() == 0) {
        // Full range
        tmp_v1->set_val_i(-1);
        tmp_v2->set_val_i(m_candidates->size()-1);

    // TODO: this should really be built after any reductions 
    //       in the valid set have been made
    // Ranges -1..N-1
        m_selector->addConstraint(ctxt->mkModelConstraintExpr(
            ctxt->mkModelExprBin(
                ctxt->mkModelExprBin(
                    ctxt->mkModelExprFieldRef(m_selector.get()),
                    BinOp::Ge,
                    ctxt->mkModelExprVal(tmp_v1.get())),
                BinOp::LogAnd,
                ctxt->mkModelExprBin(
                    ctxt->mkModelExprFieldRef(m_selector.get()),
                    BinOp::Le,
                    ctxt->mkModelExprVal(tmp_v2.get())))));
    } else { 
        // Create a custom range based on the inc ranges
        std::vector<std::pair<int32_t, int32_t>> valid_range;
        for (std::vector<IncRange>::const_iterator
            it=m_inc_ranges.begin();
            it!=m_inc_ranges.end(); it++) {
            valid_range.push_back({it->l, it->h});
        }
        std::sort(valid_range.begin(), valid_range.end(), [](
            const std::pair<int32_t,int32_t> &v1,
            const std::pair<int32_t,int32_t> &v2) { return v1.first < v2.first; });
        
        // See if we can merge some ranges
        for (uint32_t i=1; i<valid_range.size(); i++) {
            if (valid_range.at(i-1).second+1 >= valid_range.at(i).first) {
                // These ranges overlap. 
                if (valid_range.at(i-1).second <= valid_range.at(i).second) {
                    // merge the ranges
                    valid_range.at(i-1).second = valid_range.at(i).second;
                } else {
                    // Leave the end range alone, since we completely contain the range
                }
                valid_range.erase(valid_range.begin()+i);
            }
        }

        // We should now be able to formulate an overall range constraint
        if (valid_range.at(0).first == 0) {
            // Reduce this to -1 to cover the 'invalid' value
            valid_range.at(0).first = -1;
        } else {
            valid_range.insert(valid_range.begin(), {-1,-1});
        }

        if (valid_range.size() == 1) {
            tmp_v1->set_val_i(valid_range.at(0).first);
            tmp_v2->set_val_i(valid_range.at(0).second);
            DEBUG("Range: %d..%d", valid_range.at(0).first, valid_range.at(0).second);

            m_selector->addConstraint(ctxt->mkModelConstraintExpr(
                ctxt->mkModelExprBin(
                    ctxt->mkModelExprBin(
                        ctxt->mkModelExprFieldRef(m_selector.get()),
                        BinOp::Ge,
                        ctxt->mkModelExprVal(tmp_v1.get())),
                    BinOp::LogAnd,
                        ctxt->mkModelExprBin(
                          ctxt->mkModelExprFieldRef(m_selector.get()),
                          BinOp::Le,
                          ctxt->mkModelExprVal(tmp_v2.get())))));
        } else {
            DEBUG("TODO: form rangelist constraint");

            for (std::vector<std::pair<int32_t,int32_t>>::const_iterator
                it=valid_range.begin();
                it!=valid_range.end(); it++) {
                DEBUG("Range: %d..%d", it->first, it->second);
            }
        }


        // TODO: Now, form a rangelist from the intervals
    }

    // Validity constraints
    m_valid_c = IModelConstraintUP(ctxt->mkModelConstraintExpr(
        ctxt->mkModelExprBin(
            ctxt->mkModelExprFieldRef(m_selector.get()),
            BinOp::Ne,
            ctxt->mkModelExprVal(tmp_v1.get()))));

    m_valid_soft_c = IModelConstraintUP(ctxt->mkModelConstraintSoft(
        ctxt->mkModelConstraintExpr(
            ctxt->mkModelExprBin(
                ctxt->mkModelExprFieldRef(m_selector.get()),
                BinOp::Ne,
                ctxt->mkModelExprVal(tmp_v1.get())))));

    DEBUG_LEAVE("init %s", m_selector->name().c_str());
}

void RefSelector::addIncludeRange(int32_t l, int32_t h, IModelExpr *cond) {
    m_inc_ranges.push_back({l, h, IModelExprUP(cond)});
}

dmgr::IDebug *RefSelector::m_dbg = 0;

}
}
