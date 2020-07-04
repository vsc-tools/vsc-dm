/*
 * ExprBin.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRBIN_H_
#define SRC_EXPR_EXPRBIN_H_
#include "Expr.h"
#include "ExprBinOp.h"

namespace vsc {

class ExprBin : public Expr {
public:
	ExprBin(
			Expr		*lhs,
			ExprBinOp	op,
			Expr		*rhs);

	virtual ~ExprBin();

	Expr *lhs() const { return m_lhs.get(); }

	ExprBinOp op() const { return m_op; }

	Expr *rhs() const { return m_rhs.get(); }

	virtual void accept(IExprVisitor *v) { v->visitExprBin(this); }

private:
	ExprSP				m_lhs;
	ExprBinOp			m_op;
	ExprSP				m_rhs;

};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRBIN_H_ */
