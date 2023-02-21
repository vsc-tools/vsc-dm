/**
 * TaskCopyModelConstraintOnDemand.h
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
#include "vsc/dm/impl/PrettyPrinter.h"
#include "vsc/dm/impl/VisitorBase.h"
#include "vsc/dm/IContext.h"
#include "vsc/dm/IModelExpr.h"

namespace vsc {
namespace dm {

/**
 * @brief Creates a 'skinny' copy of 
 * 
 */
class TaskCopyModelConstraintOnDemand : public virtual VisitorBase {
public:
    TaskCopyModelConstraintOnDemand(IContext *ctxt, bool prune_uncopied=false) {
        m_ctxt = ctxt;
        m_prune_uncopied = prune_uncopied;
        m_expr_copy = 0;
        m_constraint_copy = 0;
    };

    virtual ~TaskCopyModelConstraintOnDemand() { }

    /**
     * @brief Copies the specified constraint, subject to requirements. 
     *        Returns the new constraint if a copy is made, and NULL
     *        if no copy is performed.
     * 
     * @param c 
     * @return IModelConstraint* 
     */
    IModelConstraint *copy(IModelConstraint *c) {
        m_constraint_copy = 0;
        m_expr_copy = 0;
        c->accept(m_this);

        return (m_constraint_copy)?m_constraint_copy:0;
    }

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) override {
        std::vector<IModelConstraint *> constraint_l;
        bool need_copy = false;

        for (std::vector<IModelConstraintUP>::const_iterator
            it=c->getConstraints().begin();
            it!=c->getConstraints().end(); it++) {

            m_constraint_copy = 0;
            (*it)->accept(m_this);

            if (m_constraint_copy) {
                need_copy = true;
                constraint_l.push_back(m_constraint_copy);
            } else {
                constraint_l.push_back(0);
            }
        }

        if (need_copy) {
            IModelConstraintBlock *block = m_ctxt->mkModelConstraintBlock(c->name());

            for (uint32_t i=0; i<c->getConstraints().size(); i++) {
                if (constraint_l.at(i)) {
                    block->addConstraint(constraint_l.at(i));
                } else if (!m_prune_uncopied) {
                    // Need to create a ref to the existing constraint
                    block->addConstraint(m_ctxt->mkModelConstraintRef(c->getConstraints().at(i).get()));
                }
            }
            m_constraint_copy = block;
        }
    }

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override {
        m_expr_copy = 0;
        m_constraint_copy = 0;
        c->expr()->accept(m_this);

        if (m_expr_copy) {
            // Need to create a clone
            m_constraint_copy = m_ctxt->mkModelConstraintExpr(m_expr_copy);
        }
    }

	virtual void visitModelConstraintForeach(IModelConstraintForeach *c) override {
        m_expr_copy = 0;
        m_constraint_copy= 0;

        c->getTarget()->accept(m_this);
        
        std::vector<IModelConstraint *> constraint_l;
        bool need_copy = false;

        for (std::vector<IModelConstraintUP>::const_iterator
            it=c->getConstraints().begin();
            it!=c->getConstraints().end(); it++) {

            m_constraint_copy = 0;
            (*it)->accept(m_this);

            if (m_constraint_copy) {
                need_copy = true;
                constraint_l.push_back(m_constraint_copy);
            } else {
                constraint_l.push_back(0);
            }
        }

        if (need_copy || m_expr_copy) {
            IModelConstraintForeach *c_c = m_ctxt->mkModelConstraintForeach(
                (m_expr_copy)?m_expr_copy:m_ctxt->mkModelExprRef(c->getTarget()),
                c->getIndexIt()->name());
            for (uint32_t i=0; i<c->getConstraints().size(); i++) {
                if (constraint_l.at(i)) {
                    c_c->addConstraint(constraint_l.at(i));
                } else if (!m_prune_uncopied) {
                    // Need to create a ref to the existing constraint
                    c_c->addConstraint(m_ctxt->mkModelConstraintRef(c->getConstraints().at(i).get()));
                }
            }

            m_constraint_copy = c_c;
        }


    }

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) override {
        m_expr_copy = 0;

        c->getCond()->accept(m_this);

        bool need_copy = false;
        IModelConstraint *true_c = 0;
        m_constraint_copy= 0;
        c->getTrue()->accept(m_this);
        if (m_constraint_copy) {
            true_c = m_constraint_copy;
            need_copy = true;
        }

        IModelConstraint *false_c = 0;
        m_constraint_copy= 0;
        if (c->getFalse()) {
            c->getFalse()->accept(m_this);
            if (m_constraint_copy) {
                false_c = m_constraint_copy;
                need_copy = true;
            }
        }

        if (m_expr_copy || need_copy) {
            IModelConstraintIfElse *c_c = m_ctxt->mkModelConstraintIfElse(
                (m_expr_copy)?m_expr_copy:m_ctxt->mkModelExprRef(c->getCond()),
                (true_c)?true_c:m_ctxt->mkModelConstraintRef(c->getTrue()),
                (false_c)?false_c:c->getFalse()?m_ctxt->mkModelConstraintRef(c->getFalse()):0);
            m_constraint_copy = c_c;
        }
    }

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override {
        m_expr_copy = 0;
        c->getCond()->accept(m_this);
        
        m_constraint_copy = 0;
        c->getBody()->accept(m_this);

        if (m_expr_copy || m_constraint_copy) {
            IModelConstraintImplies *c_c = m_ctxt->mkModelConstraintImplies(
                (m_expr_copy)?m_expr_copy:m_ctxt->mkModelExprRef(c->getCond()),
                (m_constraint_copy)?m_constraint_copy:m_ctxt->mkModelConstraintRef(c->getBody()));
            m_constraint_copy = c_c;
        }
    }

	virtual void visitModelConstraintRef(IModelConstraintRef *c) override {
        // Just pass-through for now
        c->getTarget()->accept(m_this);
    }

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override {
        m_expr_copy = 0;
        m_constraint_copy= 0;

        std::vector<IModelConstraint *> constraint_l;
        bool need_copy = false;

        for (std::vector<IModelConstraintUP>::const_iterator
            it=c->getConstraints().begin();
            it!=c->getConstraints().end(); it++) {

            m_constraint_copy = 0;
            (*it)->accept(m_this);

            if (m_constraint_copy) {
                need_copy = true;
                constraint_l.push_back(m_constraint_copy);
            } else {
                constraint_l.push_back(0);
            }
        }

        if (need_copy) {
            IModelConstraintScope *c_c = m_ctxt->mkModelConstraintScope();
            for (uint32_t i=0; i<c->getConstraints().size(); i++) {
                if (constraint_l.at(i)) {
                    c_c->addConstraint(constraint_l.at(i));
                } else if (!m_prune_uncopied) {
                    // Need to create a ref to the existing constraint
                    c_c->addConstraint(m_ctxt->mkModelConstraintRef(c->getConstraints().at(i).get()));
                }
            }

            m_constraint_copy = c_c;
        }
    }

	virtual void visitModelConstraintSelect(IModelConstraintSelect *c) override {
        // Ignore for now
    }

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override {
        m_constraint_copy = 0;
        c->constraint()->accept(m_this);

        if (m_constraint_copy) {
            m_constraint_copy = m_ctxt->mkModelConstraintSoft(
                dynamic_cast<IModelConstraintExpr *>(m_constraint_copy));
        }
    }

	virtual void visitModelConstraintSubst(IModelConstraintSubst *c) override {
        // Ignore for now
    }

	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) override {
        std::vector<IModelExpr *> expr_l;
        bool need_copy = false;
        m_constraint_copy = 0;

        for (std::vector<IModelExprUP>::const_iterator 
            it=c->getExprs().begin();
            it!=c->getExprs().end(); it++) {
            m_expr_copy = 0;
            (*it)->accept(m_this);

            need_copy |= (m_expr_copy != 0);
            expr_l.push_back(m_expr_copy);
        }

        if (need_copy) {
            for (uint32_t i=0; i<c->getExprs().size(); i++) {
                if (!expr_l.at(i)) {
                    expr_l[i] = m_ctxt->mkModelExprRef(c->getExprs().at(i).get());
                }
            }
            m_constraint_copy = m_ctxt->mkModelConstraintUnique(expr_l);
        }
    }

	virtual void visitModelExprBin(IModelExprBin *e) override {
        m_expr_copy = 0;
        e->lhs()->accept(m_this);
        IModelExpr *lhs = m_expr_copy;

        m_expr_copy = 0;
        e->rhs()->accept(m_this);
        IModelExpr *rhs = m_expr_copy;

        if (lhs || rhs) {
            m_expr_copy = m_ctxt->mkModelExprBin(
                (lhs)?lhs:m_ctxt->mkModelExprRef(e->lhs()),
                e->op(),
                (rhs)?rhs:m_ctxt->mkModelExprRef(e->rhs()));
        }
    }

	virtual void visitModelExprCond(IModelExprCond *e) override {
        m_expr_copy = 0;
        e->getCond()->accept(m_this);
        IModelExpr *cond = m_expr_copy;

        m_expr_copy = 0;
        e->getTrue()->accept(m_this);
        IModelExpr *true_e = m_expr_copy;

        m_expr_copy = 0;
        e->getFalse()->accept(m_this);
        IModelExpr *false_e = m_expr_copy;

        if (cond || true_e || false_e) {
            m_expr_copy = m_ctxt->mkModelExprCond(
                (cond)?cond:m_ctxt->mkModelExprRef(e->getCond()),
                (true_e)?true_e:m_ctxt->mkModelExprRef(e->getTrue()),
                (false_e)?false_e:m_ctxt->mkModelExprRef(e->getFalse()));
        }
    }

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override {
        m_expr_copy = 0;
    }

	virtual void visitModelExprIn(IModelExprIn *e) override {
        m_expr_copy = 0;
    }

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override {
        m_expr_copy = 0;
    }

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override {
        m_expr_copy = 0;
    }

	virtual void visitModelExprRange(IModelExprRange *e) override {
        m_expr_copy = 0;
    }

	virtual void visitModelExprRangelist(IModelExprRangelist *e) override {
        m_expr_copy = 0;
    }

	virtual void visitModelExprRef(IModelExprRef *e) override {
        m_expr_copy = 0;
        e->expr()->accept(m_this);
    }

	virtual void visitModelExprUnary(IModelExprUnary *e) override {
        m_expr_copy = 0;
        e->expr()->accept(m_this);

        if (m_expr_copy) {
            m_expr_copy = m_ctxt->mkModelExprUnary(e->op(), m_expr_copy);
        }
    }

	virtual void visitModelExprVal(IModelExprVal *e) override {
        m_expr_copy = 0;
    }

	virtual void visitModelExprVecSubscript(IModelExprVecSubscript *e) override {
        m_expr_copy = 0;
    }


protected:
    IContext                    *m_ctxt;
    bool                        m_prune_uncopied;
    IModelExpr                  *m_expr_copy;
    IModelConstraint            *m_constraint_copy;

};

}
}

