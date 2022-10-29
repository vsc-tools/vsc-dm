
#pragma once
#include <memory>
#include "vsc/IContext.h"
#include "vsc/IModelConstraint.h"
#include "vsc/IModelField.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class RefSelector;
using RefSelectorUP=std::unique_ptr<RefSelector>;
class RefSelector {
public:
    RefSelector(
        IModelField                         *ref,
        const std::vector<IModelField *>    &candidates) :
    m_ref(ref), m_candidates(candidates.begin(),  candidates.end()) { }

    using SelValConstraintM=std::unordered_map<int32_t,std::vector<IModelConstraint *>>;

    // Adds a constraint specific to the specified selector value
    void addSelValConstraint(int32_t val, IModelConstraint *c) {
        SelValConstraintM::iterator it = m_selval_constraints.find(val);

        if (it == m_selval_constraints.end()) {
            it = m_selval_constraints.insert({val, {}}).first;
        }
        it->second.push_back(c);
        m_constraints.push_back(IModelConstraintUP(c));
    }

    bool hasSelValConstraint(int32_t val) {
        return (m_selval_constraints.find(val) != m_selval_constraints.end());
    }

    const std::vector<IModelConstraint *> &getSelValConstraints(int32_t val) const {
        return m_selval_constraints.find(val)->second;
    }

    IModelField                             *m_ref;
    uint32_t                                m_bits;
    IModelFieldUP                           m_selector;
    IModelConstraintUP                      m_valid_c;
    IModelConstraintUP                      m_valid_soft_c;
    SelValConstraintM                       m_selval_constraints;
    std::vector<IModelConstraintUP>         m_constraints;
    std::vector<IModelField *>              m_candidates;
};

class TaskBuildRefSelector : public VisitorBase {
public:

    TaskBuildRefSelector(IContext *ctxt) : m_ctxt(ctxt) { }

    virtual ~TaskBuildRefSelector() {}

    RefSelector *build(
        IModelField                         *ref,
        const std::vector<IModelField *>    &candidates) {
        RefSelector *sel = new RefSelector(ref, candidates);

        // TODO:
        // Actually, all of this should be done post to allow 
        // selectors to be built before the full candidate set
        // is known
        uint32_t bits = 0, value = candidates.size();

        // Determine how many bits are needed
        do {
            bits++;
            value >>= 1;
        } while (value);

        // Create one bit larger than the max value for the sign bit
        bits++;

        IDataTypeInt *selector_t = m_ctxt->findDataTypeInt(true, bits);
        if (!selector_t) {
            selector_t = m_ctxt->mkDataTypeInt(true, bits);
            m_ctxt->addDataTypeInt(selector_t);
        }

        sel->m_bits = bits;
        sel->m_selector = IModelFieldUP(
            m_ctxt->mkModelFieldRoot(selector_t, "selector"));

        // Add a constraint on the value range
        IModelValUP tmp_v1 = IModelValUP(m_ctxt->mkModelVal());
        IModelValUP tmp_v2 = IModelValUP(m_ctxt->mkModelVal());

        tmp_v1->setBits(bits);
        tmp_v2->setBits(bits);
        tmp_v1->set_val_i(-1);
        tmp_v2->set_val_i(candidates.size()-1);

        // TODO: this should really be built after any reductions 
        //       in the valid set have been made
        // Ranges -1..N-1
        sel->m_selector->addConstraint(m_ctxt->mkModelConstraintExpr(
            m_ctxt->mkModelExprBin(
                m_ctxt->mkModelExprBin(
                    m_ctxt->mkModelExprFieldRef(sel->m_selector.get()),
                    BinOp::Ge,
                    m_ctxt->mkModelExprVal(tmp_v1.get())),
                BinOp::LogAnd,
                m_ctxt->mkModelExprBin(
                    m_ctxt->mkModelExprFieldRef(sel->m_selector.get()),
                    BinOp::Le,
                    m_ctxt->mkModelExprVal(tmp_v2.get())))));

        // Validity constraints
        sel->m_valid_c = IModelConstraintUP(m_ctxt->mkModelConstraintExpr(
            m_ctxt->mkModelExprBin(
                m_ctxt->mkModelExprFieldRef(sel->m_selector.get()),
                BinOp::Ne,
                m_ctxt->mkModelExprVal(tmp_v1.get()))));

        sel->m_valid_soft_c = IModelConstraintUP(m_ctxt->mkModelConstraintSoft(
            m_ctxt->mkModelConstraintExpr(
                m_ctxt->mkModelExprBin(
                    m_ctxt->mkModelExprFieldRef(sel->m_selector.get()),
                    BinOp::Ne,
                    m_ctxt->mkModelExprVal(tmp_v1.get())))));

        return sel;
    }


private:
    IContext                    *m_ctxt;
};

}
