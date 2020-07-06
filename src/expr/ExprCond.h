/*
 * ExprCond.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRCOND_H_
#define SRC_EXPR_EXPRCOND_H_
#include "Expr.h"

namespace vsc {

class ExprCond : public Expr {
public:

	ExprCond(
			Expr		*cond,
			Expr		*true_e,
			Expr		*false_e
			);

	virtual ~ExprCond();

	Expr *cond() const { return m_cond.get(); }

	Expr *true_e() const { return m_true_e.get(); }

	Expr *false_e() const { return m_false_e.get(); }

	virtual void accept(IVisitor *v) { v->visitExprCond(this); }

private:
	ExprSP				m_cond;
	ExprSP				m_true_e;
	ExprSP				m_false_e;

};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRCOND_H_ */
