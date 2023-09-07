/*
 * Copyright 2019-2023 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once
#include <vector>
#include "vsc/dm/IContext.h"
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

class TaskCopyModelConstraint : public virtual VisitorBase {
public:

    TaskCopyModelConstraint(IContext *ctxt) : 
        m_ctxt(ctxt), m_expr(0), m_constraint(0) { }

    virtual ~TaskCopyModelConstraint() { }

    IModelConstraint *copy(IModelConstraint *c) {
        c->accept(m_this);
        return m_constraint;
    }

    template <class T> T *copyT(IModelConstraint *c) {
        return dynamic_cast<T *>(copy(c));
    }

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) override {
        IModelConstraintBlock *cp = m_ctxt->mkModelConstraintBlock(c->name());
        push_scope(cp);
        VisitorBase::visitModelConstraintScope(c);
        pop_scope();
        m_constraint = cp;
    }

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override {
        addConstraint(m_ctxt->mkModelConstraintExpr(expr(c->expr())));
    }

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) override {
        IModelExpr *cond = expr(c->getCond());
        IModelConstraint *true_c = copy(c->getTrue());
        IModelConstraint *false_c = (c->getFalse())?copy(c->getFalse()):0;

        addConstraint(m_ctxt->mkModelConstraintIfElse(cond, true_c, false_c));
    }

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override {
        IModelExpr *cond = expr(c->getCond());
        IModelConstraint *body = copy(c->getBody());
        addConstraint(m_ctxt->mkModelConstraintImplies(cond, body));
    }

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override {
//        IModelConstraintScope *cp = m_ctxt->mkModelConstraintScope();
    }

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override {
        addConstraint(m_ctxt->mkModelConstraintSoft(
            copyT<IModelConstraintExpr>(c->constraint())
        ));
    }

	virtual void visitModelConstraintSubst(IModelConstraintSubst *c) override {
        // This really shouldn't show up in a copied constraint
    }

	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) override {
        std::vector<IModelExpr *> exprs;
        for (std::vector<IModelExprUP>::const_iterator
            it=c->getExprs().begin();
            it!=c->getExprs().end(); it++) {
            exprs.push_back(expr(it->get()));
        }

        addConstraint(m_ctxt->mkModelConstraintUnique(exprs));
    }

	virtual void visitModelExprBin(IModelExprBin *e) override {
        m_expr = m_ctxt->mkModelExprBin(
            expr(e->lhs()),
            e->op(),
            expr(e->rhs()));
    }

	virtual void visitModelExprCond(IModelExprCond *e) override {
        m_expr = m_ctxt->mkModelExprCond(
            expr(e->getCond()),
            expr(e->getTrue()),
            expr(e->getFalse()));
    }

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override {
        m_expr = m_ctxt->mkModelExprFieldRef(e->field());
    }

	virtual void visitModelExprIn(IModelExprIn *e) override {
        m_expr = m_ctxt->mkModelExprIn(
            expr(e->lhs()),
            exprT<IModelExprRangelist>(e->rangelist()));
    }

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override { 
        IModelExprIndexedFieldRef *ref = m_ctxt->mkModelExprIndexedFieldRef();
        for (std::vector<ModelExprIndexedFieldRefElem>::const_iterator
            it=e->getPath().begin();
            it!=e->getPath().end(); it++) {
            switch (it->kind) {
            case ModelExprIndexedFieldRefKind::Field:
                ref->addField(it->field);
                break;
            case ModelExprIndexedFieldRefKind::FieldIndex:
                ref->addFieldOffsetRef(it->offset);
            case ModelExprIndexedFieldRefKind::VecIndex:
                ref->addVecIndexRef(expr(it->idx_e));
                break;
            }
        }

        fprintf(stdout, "Copy::visitModelExprIndexedFieldRef: sz1=%d sz2=%d\n",
            e->getPath().size(), ref->getPath().size());
        fflush(stdout);

        m_expr = ref;
    }

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override {
        m_expr = m_ctxt->mkModelExprPartSelect(
            expr(e->lhs()),
            e->lower(),
            e->upper());
    }

	virtual void visitModelExprRange(IModelExprRange *e) override {
        m_expr = m_ctxt->mkModelExprRange(
            e->isSingle(),
            (e->lower())?expr(e->lower()):0,
            (e->upper())?expr(e->upper()):0);
    }

	virtual void visitModelExprRangelist(IModelExprRangelist *e) override {
        IModelExprRangelist *rl = m_ctxt->mkModelExprRangelist();

        for (std::vector<IModelExprRangeUP>::const_iterator
            it=e->getRanges().begin();
            it!=e->getRanges().end(); it++) {
            rl->addRange(exprT<IModelExprRange>(it->get()));
        }

        m_expr = rl;
    }

	virtual void visitModelExprRef(IModelExprRef *e) override {
        m_expr = m_ctxt->mkModelExprRef(e->expr());
    }

	virtual void visitModelExprUnary(IModelExprUnary *e) override {
        m_expr = m_ctxt->mkModelExprUnary(
            e->op(),
            e->expr());
    }

	virtual void visitModelExprVal(IModelExprVal *e) override {
#ifdef UNDEFINED
        m_expr = m_ctxt->mkModelExprVal(e->val());
#endif
    }

	virtual void visitModelExprVecSubscript(IModelExprVecSubscript *e) override {
        /*
        m_expr = m_ctxt->mkModelExprVecSubscript(
            expr(e->expr()),
            expr(e->subscript()));
         */
    }

protected:
    void push_scope(IModelConstraintScope *s) { m_scope_s.push_back(s); }

    void pop_scope() { m_scope_s.pop_back(); }

    bool have_scope() { return m_scope_s.size() > 0; }

    IModelConstraintScope *scope() { return m_scope_s.back(); }

    void addConstraint(IModelConstraint *c) {
        if (m_scope_s.size() > 0) {
            m_scope_s.back()->addConstraint(c, true);
        }
        m_constraint = c;
    }

    IModelExpr *expr(IModelExpr *e) {
        m_expr = 0;
        e->accept(m_this);
        return m_expr;
    }

    template <class T> T *exprT(IModelExpr *e) {
        return dynamic_cast<T *>(expr(e));
    }

protected:
    IContext                                *m_ctxt;
    IModelConstraint                        *m_constraint;
    IModelExpr                              *m_expr;
    std::vector<IModelConstraintScope *>    m_scope_s;


};

}
}
