/*
 * ConstraintStmtExpr.h
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#ifndef SRC_CONSTRAINTS_CONSTRAINTEXPR_H_
#define SRC_CONSTRAINTS_CONSTRAINTEXPR_H_
#include "constraints/ConstraintStmt.h"
#include "expr/Expr.h"

namespace vsc {

class ConstraintExpr : public ConstraintStmt {
public:
	ConstraintExpr(Expr *expr);

	virtual ~ConstraintExpr();

	Expr *expr() const { return m_expr.get(); }

	virtual void accept(IVisitor *v) { v->visitConstraintExpr(this); }

private:
	ExprSP				m_expr;
};

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTEXPR_H_ */
