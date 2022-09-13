
#pragma once
#include <memory>
#include <vector>
#include "vsc/IContext.h"

#include "vsc/impl/TaskCopyModelConstraintOnDemand.h"

namespace vsc {

class ModelFieldRefConstraintData;
using ModelFieldRefConstraintDataUP=std::unique_ptr<ModelFieldRefConstraintData>;
class ModelFieldRefConstraintData {
public:

    ModelFieldRefConstraintData(
        IModelField         *selector,
        IModelConstraint    *valid_c,
        IModelConstraint    *valid_soft_c) : m_selector(selector),
        m_valid_c(valid_c), m_valid_soft_c(valid_soft_c) { }

    IModelField *getSelector() const { return m_selector.get(); }

    int32_t getNumCandidates() const { return m_select_c_l.size(); }

    void addSelectC(IModelConstraintScope *c) { m_select_c_l.push_back(IModelConstraintScopeUP(c)); }

    const std::vector<IModelConstraintScopeUP> &getSelectConstraints() const { return m_select_c_l; }

    IModelConstraintScope *getSelectConstraint(int32_t idx) const { return m_select_c_l.at(idx).get(); }

    IModelConstraint *getValidC() const { return m_valid_c.get(); }

    IModelConstraint *getValidSoftC() const { return m_valid_soft_c.get(); }

protected:
    IModelFieldUP                               m_selector;
    IModelConstraintScopeUP                     m_core_c;
    std::vector<IModelConstraintScopeUP>        m_select_c_l;
    IModelConstraintUP                          m_valid_c;
    IModelConstraintUP                          m_valid_soft_c;

};

/**
 * @brief Builds a selector structure for a reference field
 * 
 * - Accepts the reference field, a set of candidates, and a set of
 *   constraints (optionally) containing references to fields via 
 *   the reference field.
 */
class TaskUnrollModelFieldRefConstraints : public virtual TaskCopyModelConstraintOnDemand {
public:
    TaskUnrollModelFieldRefConstraints(IContext *ctxt) : TaskCopyModelConstraintOnDemand(ctxt) { 
        m_candidate_refs = 0;

    }

    ModelFieldRefConstraintData *build(
        IModelFieldRef                          *ref, // target reference
        const std::vector<IModelField *>        &candidates,
        const std::vector<IModelFieldRef *>     &candidate_refs, // (optional)
        const std::vector<IModelConstraint *>   &constraints) {
        uint32_t bits = 0, value = candidates.size();

        m_candidate_refs = (candidate_refs.size())?&candidate_refs:0;

        // Determine how many bits are needed
        do {
            bits++;
            value >>= 1;
        } while (value);

        IDataTypeInt *selector_t = m_ctxt->findDataTypeInt(true, bits);
        if (!selector_t) {
            selector_t = m_ctxt->mkDataTypeInt(true, bits);
            m_ctxt->addDataTypeInt(selector_t);
        }

        IModelField *selector = m_ctxt->mkModelFieldRoot(selector_t, "selector");

        // Add a constraint on the value range
        IModelValUP tmp_v1 = IModelValUP(m_ctxt->mkModelVal());
        IModelValUP tmp_v2 = IModelValUP(m_ctxt->mkModelVal());

        tmp_v1->setBits(bits);
        tmp_v2->setBits(bits);
        tmp_v1->set_val_i(-1);
        tmp_v2->set_val_i(candidates.size()-1);

        // Ranges -1..N-1
        selector->addConstraint(m_ctxt->mkModelConstraintExpr(
            m_ctxt->mkModelExprBin(
                m_ctxt->mkModelExprBin(
                    m_ctxt->mkModelExprFieldRef(selector),
                    BinOp::Ge,
                    m_ctxt->mkModelExprVal(tmp_v1.get())),
                BinOp::LogAnd,
                m_ctxt->mkModelExprBin(
                    m_ctxt->mkModelExprFieldRef(selector),
                    BinOp::Le,
                    m_ctxt->mkModelExprVal(tmp_v2.get())))));

        IModelConstraint *valid_c = m_ctxt->mkModelConstraintExpr(
            m_ctxt->mkModelExprBin(
                m_ctxt->mkModelExprFieldRef(selector),
                BinOp::Ne,
                m_ctxt->mkModelExprVal(tmp_v1.get())));

        IModelConstraint *valid_soft_c = m_ctxt->mkModelConstraintSoft(
            m_ctxt->mkModelConstraintExpr(
                m_ctxt->mkModelExprBin(
                    m_ctxt->mkModelExprFieldRef(selector),
                    BinOp::Ne,
                    m_ctxt->mkModelExprVal(tmp_v1.get()))));

        m_result = ModelFieldRefConstraintDataUP(new ModelFieldRefConstraintData(
                selector, valid_c, valid_soft_c));

        for (uint32_t i=0; i<candidates.size(); i++) {
            m_tmp_c = IModelConstraintScopeUP(m_ctxt->mkModelConstraintScope());

            // TODO: build out constraints
            // (selector == i) -> {
            //   (constraints via 'ref')
            //   (constraints via 'candidate_refs[i]')
            // }

            m_target_ref = ref;
            m_candidate = candidates.at(i);

            // TODO: need a way to pass constraint-scope down
            for (std::vector<IModelConstraint *>::const_iterator
                c_it=constraints.begin();
                c_it!=constraints.end(); c_it++) {
                (*c_it)->accept(m_this);
            }

            if (candidate_refs.size()) {
                m_target_ref = candidate_refs.at(i);
                for (std::vector<IModelConstraint *>::const_iterator
                    c_it=constraints.begin();
                    c_it!=constraints.end(); c_it++) {
                    (*c_it)->accept(m_this);
                }
            }

            m_result->addSelectC(m_tmp_c.release());
        }

        return m_result.release();
    }

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override {

/*
        // Step through to see if we hit the target
        int32_t i=0;
        for (; i<e->getPath().size(); i++) {
            IModelField *

        }
 */


        m_expr_copy = 0;
    }

private:
    IModelConstraintScopeUP                     m_tmp_c;
    ModelFieldRefConstraintDataUP               m_result;
    IModelField                                 *m_target_ref;
    IModelField                                 *m_candidate;
    const std::vector<IModelField *>            *m_candidate_refs;


};

}