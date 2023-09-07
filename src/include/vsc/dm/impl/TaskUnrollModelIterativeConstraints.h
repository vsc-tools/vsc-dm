#pragma once
#include <vector>
#include <map>
#include "vsc/dm/impl/TaskCopyModelConstraint.h"
#include "vsc/dm/impl/TaskResolveModelExprFieldRef.h"

namespace vsc {
namespace dm {

class TaskUnrollModelIterativeConstraints : 
    public virtual TaskCopyModelConstraint {
public:

    TaskUnrollModelIterativeConstraints(IContext *ctxt) : TaskCopyModelConstraint(ctxt) { 
        m_foreach_depth = 0;
    }

    virtual ~TaskUnrollModelIterativeConstraints() { }

    void unroll(
        IModelConstraintScope                 *dst,
        const std::vector<IModelConstraint *> &constraints) {
        m_dst = dst;
        m_src_scope_s.push_back(dst);
        for (std::vector<IModelConstraint *>::const_iterator
            it=constraints.begin();
            it!=constraints.end(); it++) {
            m_foreach_depth = 0;
            (*it)->accept(m_this);
        }
        m_src_scope_s.pop_back();
    }

    void unroll(
        IModelConstraintScope   *dst,
        IModelConstraint        *c) {
        m_dst = dst;
        m_src_scope_s.push_back(dst);
        m_foreach_depth = 0;
        c->accept(m_this);
        m_src_scope_s.pop_back();
    }

	virtual void visitModelConstraint(IModelConstraint *c) override {

    }

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) override {
        if (m_foreach_depth) {
            TaskCopyModelConstraint::visitModelConstraintBlock(c);
        } else {
            VisitorBase::visitModelConstraintBlock(c);
        }
    }

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override {
        if (m_foreach_depth) {
            TaskCopyModelConstraint::visitModelConstraintExpr(c);
        } else {
            if (m_src_scope_s.back() == m_dst) {
                // Need to hook the constraint on here
                m_scope_s.back()->addConstraint(m_ctxt->mkModelConstraintRef(c), true);
            }
            // Otherwise, the constraint is already attached to a referenced scope
        }
    }

	virtual void visitModelConstraintForeach(IModelConstraintForeach *c) override {
        IModelConstraintScope *scope;

        if (m_foreach_depth) {
            // This is the second+ level of the foreach
            // Create a scope to hold the new constraints
            scope = m_ctxt->mkModelConstraintScope();
        } else {
            // Need to replace this foreach in the parent
            if (m_src_scope_s.back() == m_dst) {
                // We're adding data to the false root
                scope = m_ctxt->mkModelConstraintScope();
                m_src_scope_s.back()->addConstraint(scope, true);
            } else {
                // We're within an original source scope
                IModelConstraintSubst *subst = m_ctxt->mkModelConstraintSubst(c);

                // Replace the existing constraint with the substitute
                /*
                m_src_scope_s.back()->swapConstraint(m_src_index_s.back(), subst);
                 */

                scope = subst;
            }
        }

        m_foreach_depth++;
        m_scope_s.push_back(scope);
        IModelFieldVec *vec = TaskResolveModelExprFieldRef(m_ctxt).resolveT<IModelFieldVec>(0, c->getTarget());
        ModelFieldFlag flags = c->getIndexIt()->flags();
        c->getIndexIt()->setFlag(ModelFieldFlag::Resolved);
        for (uint32_t i=0; i<vec->getSize(); i++) {
#ifdef UNDEFINED
            c->getIndexIt()->val()->set_val_u(i);
#endif
            for (std::vector<IModelConstraintUP>::const_iterator
                it=c->getConstraints().begin();
                it!=c->getConstraints().end(); it++) {
                fprintf(stdout, "--> visitForeachConstraint\n");
                (*it)->accept(m_this);
                fprintf(stdout, "<-- visitForeachConstraint\n");
            }
        }
        c->getIndexIt()->setFlags(flags);
        m_scope_s.pop_back();

        m_foreach_depth--;
    }

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) override {
        if (m_foreach_depth) {
            TaskCopyModelConstraint::visitModelConstraintIfElse(c);
        } else {
            if (m_src_scope_s.back() == m_dst) {
                m_dst->addConstraint(m_ctxt->mkModelConstraintRef(c), true);
            }
            VisitorBase::visitModelConstraintIfElse(c);
        }
    }

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override {
        if (m_foreach_depth) {
            TaskCopyModelConstraint::visitModelConstraintImplies(c);
        } else {
            if (m_src_scope_s.back() == m_dst) {
                m_dst->addConstraint(m_ctxt->mkModelConstraintRef(c), true);
            }
            VisitorBase::visitModelConstraintImplies(c);
        }
    }

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override {
        if (m_foreach_depth) {
            // We're copying...
            TaskCopyModelConstraint::visitModelConstraintScope(c);
        } else {
            if (m_src_scope_s.back() == m_dst) {
                m_dst->addConstraint(m_ctxt->mkModelConstraintRef(c), true);
            }

            m_src_scope_s.push_back(c);

            m_src_index_s.push_back(0);
            for (uint32_t i=0; i<c->getConstraints().size(); i++) {
                m_src_index_s.back() = i;
                c->getConstraints().at(i)->accept(m_this);
            }
            m_src_index_s.pop_back();
            m_src_scope_s.pop_back();
        }
    }

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override {
        if (m_foreach_depth) {
            TaskCopyModelConstraint::visitModelConstraintSoft(c);
        } else {
            if (m_src_scope_s.back() == m_dst) {
                m_dst->addConstraint(m_ctxt->mkModelConstraintRef(c), true);
            }
            VisitorBase::visitModelConstraintSoft(c);
        }
    }

	virtual void visitModelConstraintSubst(IModelConstraintSubst *c) override {
        // Shouldn't hit that here...
        if (m_foreach_depth) {
            TaskCopyModelConstraint::visitModelConstraintSubst(c);
        } else {
            VisitorBase::visitModelConstraintSubst(c);
        }
    }

	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) override {
        if (m_foreach_depth) {
            TaskCopyModelConstraint::visitModelConstraintUnique(c);
        } else {
            if (m_src_scope_s.back() == m_dst) {
                m_dst->addConstraint(m_ctxt->mkModelConstraintRef(c), true);
            }
            VisitorBase::visitModelConstraintUnique(c);
        }
    }

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override {
        if (m_foreach_depth) {
            // For iterative constraints, flatten out any const references
            if (e->field()->isFlagSet(ModelFieldFlag::Resolved)) {
#ifdef UNDEFINED
                 IModelVal *val = m_ctxt->mkModelVal();
                 val->set(e->field()->val());
                 m_expr = m_ctxt->mkModelExprVal(val);
#endif
            } else {
                 m_expr = m_ctxt->mkModelExprFieldRef(e->field());
            }
        }
    }

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override {
	    IModelField *field = TaskResolveModelExprFieldRef(m_ctxt).resolve(0, e);
        m_expr = m_ctxt->mkModelExprFieldRef(field);
    }

protected:
    IModelConstraintScope                     *m_dst;
    std::vector<IModelConstraintScope *>      m_src_scope_s;
    std::vector<uint32_t>                     m_src_index_s;
    uint32_t                                  m_foreach_depth;
//    std::map<IModelField *, IModelVal *>      m_iter_val_m;
};


}
}

