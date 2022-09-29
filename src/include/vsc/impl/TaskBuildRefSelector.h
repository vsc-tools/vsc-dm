
#pragma once
#include <memory>
#include "vsc/IContext.h"
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

    IModelField                             *m_ref;
    uint32_t                                m_bits;
    IModelFieldUP                           m_selector;
    IModelConstraintUP                      m_valid_c;
    IModelConstraintUP                      m_valid_soft_c;
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
