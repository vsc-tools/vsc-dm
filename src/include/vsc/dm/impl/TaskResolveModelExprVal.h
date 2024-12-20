
#pragma once
#include "vsc/dm/IContext.h"
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

class TaskResolveModelExprVal : public virtual VisitorBase {
public:
    static const int32_t Kind_Int = 1;
    static const int32_t Kind_String = (Kind_Int+1);
    static const int32_t Kind_Struct = (Kind_String+1);
    static const int32_t Kind_Last   = Kind_Struct;

    struct ValInfo {
        int32_t             kind;
        ValRef              val;
    };

public:

    TaskResolveModelExprVal(IContext *ctxt) : m_ctxt(ctxt) {
        m_resolved = true;
    }

    virtual ~TaskResolveModelExprVal() { }

    ValInfo eval(
        IModelExpr      *expr,
        int32_t         width=-1) {
//        m_result = result;
        m_width = width;

        expr->accept(m_this);

        return m_val;
    }


	virtual void visitModelExprBin(IModelExprBin *e) override {
        bool resolved = true;
        
        // Must know kind of LHS, RHS in order to 'route' to implementation
        //
        // 
        ValInfo lhs = _eval(e->lhs());
        ValInfo rhs = _eval(e->rhs());

        if (lhs.kind != rhs.kind) {
            fprintf(stdout, "Error: kind mismatch\n");
        }

//        m_val = evalExprBin(lhs, e->op(), rhs);
    }

    virtual ValInfo evalExprBin(
        const ValInfo           &lhs,
        BinOp                   op,
        const ValInfo           &rhs) {
        if (lhs.kind == Kind_Int) {
            ValRefInt lhs_r = ValRefInt(lhs.val);
            ValRefInt rhs_r = ValRefInt(rhs.val);

            if (lhs_r.bits() <= ValRefInt::native_sz() &&
                rhs_r.bits() <= ValRefInt::native_sz() &&
                m_width <= ValRefInt::native_sz()) {
                // Everything is native size or smaller, so
                // perform the computation using native ops
//                return evalExprBinIntNative(lhs, op, rhs);
            } else {
                // We exceed native size, so 

            }

//            if (lhs_r.bits() < m_width || lhs_r.bits() < lhs_r.bits())) {
//                lhs_r = lhs_r.signExt(max())
//            }

        } else if (lhs.kind == Kind_String) {
            // Only '==' and '!=' supported
            if (op != BinOp::Eq && op != BinOp::Ne) {
                fprintf(stdout, "Error: unsupported string operator\n");
            }
        } else if (lhs.kind == Kind_Struct) {

        }
        return ValInfo();
    }

    virtual ValInfo evalExprBinIntNative(
        const ValRefInt         &lhs,
        BinOp                   op,
        const ValRefInt         &rhs) {

//        bool is_signed = (lhs.is_signed() || rhs.is_signed());
        return ValInfo();
    }

    virtual void foo() {
#ifdef UNDEFINED
        IModelValOp *op = m_ctxt->getModelValOp();
        ValRef lhs;
        IModelVal *lhs_v = alloc_v(e->width());
        resolved &= m_resolved;
        bool lhs_signed = _eval(lhs_v, e->lhs());
        IModelVal *rhs_v = alloc_v(e->width());
        bool rhs_signed = _eval(rhs_v, e->rhs());
        resolved &= m_resolved;

        if (!resolved) {
            m_resolved = false;
            return;
        }

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
   		case BinOp::Sub: op->sub(m_result, lhs_v, rhs_v); break; 
   		case BinOp::Xor: op->bin_xor(m_result, lhs_v, rhs_v); break;
   		case BinOp::BinAnd: op->bin_and(m_result, lhs_v, rhs_v); break;
   		case BinOp::BinOr: op->bin_or(m_result, lhs_v, rhs_v); break;
	    }
        free_v(lhs_v);
        free_v(rhs_v);
#endif /* UNDEFINED */
    }

	virtual void visitModelExprCond(IModelExprCond *e) override {
        /*
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
         */
    }

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override {
//        m_result.set(e->field()->getVal(false)); // Get immutable ref to the value
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
        m_result.set(e->getVal());
    }

protected:
    IModelVal *alloc_v(int32_t width) {
        /*
        IModelVal *val;
        if (m_val_s.size()) {
            val = m_val_s.back().release();
            m_val_s.pop_back();
        } else {
            val = m_ctxt->mkModelVal();
        }
        val->setBits(width);
        return val;
         */
        return 0;
    }

    void free_v(IModelVal *v) {
        /*
        m_val_s.push_back(IModelValUP(v));
         */
    }

    ValInfo _eval(IModelExpr *expr) {
#ifdef UNDEFINED
        m_resolved = true;
        IModelVal *result_t = m_result;
        m_result = result;
        expr->accept(m_this);
        m_result = result_t;
        return m_signed;
#endif /* UNDEFINED */
        return ValInfo();
    }

protected:
    IContext                    *m_ctxt;
    ValInfo                     m_val;
    ValRef                      m_result;
    std::vector<ValRef>         m_val_s;
    bool                        m_resolved;
    int32_t                     m_width;
    bool                        m_signed;

};

}
}
