
#pragma once
#include "vsc/IContext.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class TaskResolveModelExprVal : public virtual VisitorBase {
public:

    TaskResolveModelExprVal(IContext *ctxt) : m_ctxt(ctxt), m_result(0) { 
        m_resolved = true;
    }

    virtual ~TaskResolveModelExprVal() { }

    bool eval(
        IModelVal       *result,
        IModelExpr      *expr,
        int32_t         width=-1) {
        m_result = result;
        m_width = width;

        expr->accept(m_this);

        return m_signed;
    }


	virtual void visitModelExprBin(IModelExprBin *e) override {
        IModelValOp *op = m_ctxt->getModelValOp();
        IModelVal *lhs_v = alloc_v(e->width());
        bool lhs_signed = _eval(lhs_v, e->lhs());
        IModelVal *rhs_v = alloc_v(e->width());
        bool rhs_signed = _eval(rhs_v, e->rhs());

        if (lhs_v->bits() > m_width) {
            m_width = lhs_v->bits();
        }

        if (rhs_v->bits() > m_width) {
            m_width = rhs_v->bits();
        }

        m_signed = (lhs_signed || rhs_signed);
        m_result->setBits(m_width);

   		switch (e->op()) {
   		case BinOp::Add: op->add(m_result, lhs_v, rhs_v); break;
   		case BinOp::Eq: {
            op->eq(m_result, lhs_v, rhs_v); 
            fprintf(stdout, "lhs=%lld rhs=%lld result=%lld\n",
                lhs_v->val_u(), rhs_v->val_u(), m_result->val_u());
        } break;
   		case BinOp::Ne: op->ne(m_result, lhs_v, rhs_v); break;
   		case BinOp::Ge: 
		    // Expression must be signed or unsigned
   			if (m_signed) {
                op->sge(m_result, lhs_v, rhs_v);
   			} else {
                op->uge(m_result, lhs_v, rhs_v);
		    }
   			break;
   		case BinOp::Gt:
		    // Expression must be signed or unsigned
   			if (m_signed) {
                op->sgt(m_result, lhs_v, rhs_v);
   			} else {
                op->ugt(m_result, lhs_v, rhs_v);
   			}
   			break;
   		case BinOp::Le:
		    // Expression must be signed or unsigned
   			if (m_signed) {
   				op->sle(m_result, lhs_v, rhs_v);
   			} else {
   				op->ule(m_result, lhs_v, rhs_v);
   			}
  			break;
   		case BinOp::Lt:
		    // Expression must be signed or unsigned
   			if (m_signed) {
   				op->slt(m_result, lhs_v, rhs_v);
   			} else {
   				op->ult(m_result, lhs_v, rhs_v);
   			}
   			break;
   		case BinOp::LogAnd: op->log_and(m_result, lhs_v, rhs_v); break;
   		case BinOp::LogOr: op->log_or(m_result, lhs_v, rhs_v); break;
   		case BinOp::Sll: op->sll(m_result, lhs_v, rhs_v); break;
   		case BinOp::Srl: op->srl(m_result, lhs_v, rhs_v); break;
   		case BinOp::Sub: 
		    if (m_signed) {
                /*
   				dst->val_u(lhs.val_i() - rhs.val_i(), m_width);
   				dst->bits(m_width);
                 */
   			} else {
                /*
		    	dst->val_u(lhs.val_u() - rhs.val_u(), m_width);
   				dst->bits(m_width);
                 */
   			}
		    break;
            /*
   		case BinOp::Xor: op->xor(m_result, lhs_v, rhs_v); break;
   		case BinOp::BinAnd: op->bin_and(m_result, lhs_v, rhs_v); break;
   		case BinOp::BinOr: op->bin_or(m_result, lhs_v, rhs_v); break;
         */
	    }
        free_v(lhs_v);
        free_v(rhs_v);
    }

	virtual void visitModelExprCond(IModelExprCond *e) override {
        IModelVal *cond_v = alloc_v(1);
        _eval(cond_v, e->getCond());
        if (e->width() > m_width) {
            m_width = e->width();
        }
        m_result->setBits(m_width);
        if (cond_v->val_u()) {
            m_signed = _eval(m_result, e->getTrue());
        } else {
            m_signed = _eval(m_result, e->getFalse());
        }
    }

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override {
        m_result->set(e->field()->val());
        fprintf(stdout, "Field: %lld %lld\n", e->field()->val()->val_u(), m_result->val_u());
    }

	virtual void visitModelExprIn(IModelExprIn *e) override {

    }

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override {

    }

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override {

    }

	virtual void visitModelExprRange(IModelExprRange *e) override {

    }

	virtual void visitModelExprRangelist(IModelExprRangelist *e) override {

    }

	virtual void visitModelExprRef(IModelExprRef *e) override {
        e->accept(m_this);
    }

	virtual void visitModelExprUnary(IModelExprUnary *e) override {

    }

	virtual void visitModelExprVal(IModelExprVal *e) override {
        m_result->set(e->val());
    }

protected:
    IModelVal *alloc_v(int32_t width) {
        IModelVal *val;
        if (m_val_s.size()) {
            val = m_val_s.back().release();
            m_val_s.pop_back();
        } else {
            val = m_ctxt->mkModelVal();
        }
        val->setBits(width);
        return val;
    }

    void free_v(IModelVal *v) {
        m_val_s.push_back(IModelValUP(v));
    }

    bool _eval(
        IModelVal       *result,
        IModelExpr      *expr) {
        m_resolved = true;
        IModelVal *result_t = m_result;
        m_result = result;
        expr->accept(m_this);
        m_result = result_t;
        return m_signed;
    }

protected:
    IContext                    *m_ctxt;
    IModelVal                   *m_result;
    std::vector<IModelValUP>    m_val_s;
    bool                        m_resolved;
    int32_t                     m_width;
    bool                        m_signed;

};

}