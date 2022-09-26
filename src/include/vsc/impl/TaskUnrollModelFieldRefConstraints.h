
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

protected:
    IModelFieldUP                               m_selector;
    IModelConstraintScopeUP                     m_core_c;
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
    TaskUnrollModelFieldRefConstraints(IContext *ctxt) : TaskCopyModelConstraintOnDemand(ctxt) { 
        m_candidate_refs = 0;

    }

    ModelFieldRefConstraintData *build(
        IModelFieldRef                          *ref, // target reference
        const std::vector<IModelField *>        &candidates,
        const std::vector<IModelFieldRef *>     &candidate_refs, // (optional)
        const std::vector<IModelConstraint *>   &constraints) {
        uint32_t bits = 0, value = candidates.size();

        m_candidates = &candidates;
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
                selector, candidates, valid_c, valid_soft_c));

        for (uint32_t i=0; i<candidates.size(); i++) {
            m_tmp_c = IModelConstraintScopeUP(m_ctxt->mkModelConstraintScope());

            // TODO: build out constraints
            // (selector == i) -> {
            //   (constraints via 'ref')
            //   (constraints via 'candidate_refs[i]')
            // }

            // First, see if there are constraints here
            std::vector<IModelConstraint *> impl_constraints;
            m_target_ref = ref;
            m_candidate = candidates.at(i);

            // TODO: need a way to pass constraint-scope down
            for (std::vector<IModelConstraint *>::const_iterator
                c_it=constraints.begin();
                c_it!=constraints.end(); c_it++) {
                IModelConstraint *cc = copy(*c_it);
                fprintf(stdout, "cc: %p\n", cc);
                if (cc) {
                    impl_constraints.push_back(cc);
                }
            }

            if (candidate_refs.size()) {
                m_target_ref = candidate_refs.at(i);
                for (std::vector<IModelConstraint *>::const_iterator
                    c_it=constraints.begin();
                    c_it!=constraints.end(); c_it++) {
                    IModelConstraint *cc = copy(*c_it);
                    fprintf(stdout, "cc: %p\n", cc);
                    if (cc) {
                        impl_constraints.push_back(cc);
                    }
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

                tmp_v1->set_val_i(i);
                IModelConstraintImplies *impl = m_ctxt->mkModelConstraintImplies(
                    m_ctxt->mkModelExprBin(
                        m_ctxt->mkModelExprFieldRef(selector),
                        BinOp::Eq,
                        m_ctxt->mkModelExprVal(tmp_v1.get())),
                        body
                    );
                m_result->addSelectC(impl);
            } else {
                m_result->addSelectC(0);
            }

        }

        return m_result.release();
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

            fprintf(stdout, "field=%p m_target_ref=%p\n", field, m_target_ref);
            if (field == m_target_ref) {
                fprintf(stdout, "Match:\n");
                i++;
                field = m_candidate;
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

            fprintf(stdout, "New copy: old=%p new=%p\n", e, e_c);

            m_expr_copy = e_c;
        }
    }

private:
    IModelConstraintScopeUP                     m_tmp_c;
    ModelFieldRefConstraintDataUP               m_result;
    IModelField                                 *m_target_ref;
    IModelField                                 *m_candidate;
    const std::vector<IModelFieldRef *>         *m_candidate_refs;
    const std::vector<IModelField *>            *m_candidates;


};

}