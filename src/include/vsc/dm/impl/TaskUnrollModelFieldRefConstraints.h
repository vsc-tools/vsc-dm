
#pragma once
#include <memory>
#include <vector>
#include "vsc/dm/IContext.h"
#include "vsc/dm/IRefSelector.h"

#include "vsc/dm/impl/TaskCopyModelConstraintOnDemand.h"

namespace vsc {
namespace dm {

class ModelFieldRefConstraintData;
using ModelFieldRefConstraintDataUP=std::unique_ptr<ModelFieldRefConstraintData>;
class ModelFieldRefConstraintData {
public:

    ModelFieldRefConstraintData(
        IModelField                         *selector,
        const std::vector<IModelField *>    &candidates,
        IModelConstraint                    *valid_c,
        IModelConstraint                    *valid_soft_c) : 
            m_selector(selector), m_candidates(candidates.begin(), candidates.end()),
            m_valid_c(valid_c), m_valid_soft_c(valid_soft_c) { }

    IModelField *getSelector() const { return m_selector.get(); }

    int32_t getNumCandidates() const { return m_select_c_l.size(); }

    void addSelectC(IModelConstraint *c) { m_select_c_l.push_back(IModelConstraintUP(c)); }

    const std::vector<IModelConstraintUP> &getSelectConstraints() const { return m_select_c_l; }

    IModelConstraint *getSelectConstraint(int32_t idx) const { return m_select_c_l.at(idx).get(); }

    IModelConstraint *getValidC() const { return m_valid_c.get(); }

    IModelConstraint *getValidSoftC() const { return m_valid_soft_c.get(); }

    IModelField *getSelected() const { 
        return m_candidates.at(m_selector->val()->val_u()); 
    }

    void addFieldsConstraints(
        std::vector<IModelField *>          &fields,
        std::vector<IModelConstraint *>     &constraints,
        bool                                add_valid_c=true) const {
        fields.push_back(m_selector.get());
        for (std::vector<IModelConstraintUP>::const_iterator
            it=m_select_c_l.begin();
            it!=m_select_c_l.end(); it++) {
            if (it->get()) {
                constraints.push_back(it->get());
            }
        }
        if (add_valid_c) {
            constraints.push_back(m_valid_c.get());
        }
    }

protected:
    IModelFieldUP                               m_selector;
    std::vector<IModelConstraintUP>             m_select_c_l;
    IModelConstraintUP                          m_valid_c;
    IModelConstraintUP                          m_valid_soft_c;
    std::vector<IModelField *>                  m_candidates;

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
    TaskUnrollModelFieldRefConstraints(IContext *ctxt) : 
        TaskCopyModelConstraintOnDemand(ctxt, true) { 
        m_result = 0;
    }

    void build(
        std::vector<IModelConstraintUP>         &result,
        const std::vector<IRefSelector *>       &selectors,
        const std::vector<IModelConstraint *>   &constraints) {

        m_result = &result;

        // Target refs holds the ref fields we're looking for
        std::vector<IModelValUP> sel_values;

        // Setup a target-ref list and a list for holding values
        m_target_ref_l.clear();
        for (std::vector<IRefSelector *>::const_iterator
            it=selectors.begin();
            it!=selectors.end(); it++) {
            m_target_ref_l.push_back((*it)->getRef());
            sel_values.push_back(IModelValUP(m_ctxt->mkModelVal()));
            sel_values.back()->setBits((*it)->getSelectorBits());
        }

        process_selector(selectors, constraints, sel_values, 0);
    }

    void process_selector(
        const std::vector<IRefSelector *>           &selectors, 
        const std::vector<IModelConstraint *>       &constraints,
        const std::vector<IModelValUP>              &sel_values,
        uint32_t                                    i) {
        IRefSelector *sel = selectors.at(i);

        for (uint32_t ci=0; ci<sel->getCandidates().size(); ci++) {
            if (sel->getCandidates().at(ci)) {
                m_candidate_l.push_back(sel->getCandidates().at(ci));
                sel_values.at(i)->set_val_i(ci);

                if (i+1 < selectors.size()) {
                    process_selector(selectors, constraints, sel_values, i+1);
                } else {
                    // Go ahead and process the constraints
                    std::vector<IModelConstraint *> impl_constraints;

                    for (std::vector<IModelConstraint *>::const_iterator
                        c_it=constraints.begin();
                        c_it!=constraints.end(); c_it++) {
                        IModelConstraint *cc = copy(*c_it);
                        if (cc) {
                            impl_constraints.push_back(cc);
                        }
                    }

                    if (impl_constraints.size()) {
                        // Now, build the implication constraint
                        IModelConstraint *body = impl_constraints.at(0);
                        if (impl_constraints.size() > 1) {
                            IModelConstraintScope *body_s = m_ctxt->mkModelConstraintScope();
                            for (std::vector<IModelConstraint *>::const_iterator
                                it=impl_constraints.begin();
                                it!=impl_constraints.end(); it++) {
                                body_s->addConstraint(*it);
                            }
                            body = body_s;
                        }

                        IModelExpr *cond = 0;
                        for (uint32_t vi=0; vi<selectors.size(); vi++) {
                            IModelExpr *cc = m_ctxt->mkModelExprBin(
                                m_ctxt->mkModelExprFieldRef(selectors.at(vi)->getSelector()),
                                BinOp::Eq,
                                m_ctxt->mkModelExprVal(sel_values.at(vi).get())
                            );

                            if (!cond) {
                                cond = cc;
                            } else {
                                cond = m_ctxt->mkModelExprBin(
                                    cond,
                                    BinOp::LogAnd,
                                    cc
                                );
                            }
                        }

                        IModelConstraintImplies *impl = m_ctxt->mkModelConstraintImplies(
                            cond,
                            body
                        );

                        m_result->push_back(IModelConstraintUP(impl));
                    }
                }

                m_candidate_l.pop_back();
            }
        }
    }

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override {
        IModelField *field = 0;

        m_expr_copy = 0;

        int32_t i=0;
        for (i=0; i<e->getPath().size(); i++) {
            switch (e->getPath().at(i).kind) {
                case ModelExprIndexedFieldRefKind::Field:
                    field = e->getPath().at(i).field;
                    break;
                case ModelExprIndexedFieldRefKind::FieldIndex:
                    field = field->getField(e->getPath().at(i).offset);
                    break;
                case ModelExprIndexedFieldRefKind::VecIndex:
                    fprintf(stdout, "Error: VecIndex not supported\n");
                    field = 0;
                    break;
            }

            bool found = false;
            for (uint32_t fi=0; fi<m_target_ref_l.size(); fi++) {
                if (field == m_target_ref_l.at(fi)) {
                    field = m_candidate_l.at(fi);
                    found = true;
                    break;
                }
            }

            if (found) {
                i++;
                break;
            }
        }

        if (i < e->getPath().size()) {
            // Replace this reference with one relative to the target field
            IModelExprIndexedFieldRef *e_c = m_ctxt->mkModelExprIndexedFieldRef();
            e_c->addField(field);

            for (; i<e->getPath().size(); i++) {
                switch (e->getPath().at(i).kind) {
                    case ModelExprIndexedFieldRefKind::Field:
                        e_c->addField(e->getPath().at(i).field);
                        break;
                    case ModelExprIndexedFieldRefKind::FieldIndex:
                        e_c->addFieldOffsetRef(e->getPath().at(i).offset);
                        break;
                    case ModelExprIndexedFieldRefKind::VecIndex:
                        e_c->addVecIndexRef(m_ctxt->mkModelExprRef(e->getPath().at(i).idx_e));
                        break;
                }
            }

            m_expr_copy = e_c;
        }
    }

private:
    IModelConstraintScopeUP                     m_tmp_c;
    std::vector<IModelField *>                  m_target_ref_l;
    std::vector<IModelField *>                  m_candidate_l;
    std::vector<IModelConstraintUP>             *m_result;


};

}
}
