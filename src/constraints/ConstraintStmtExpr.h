/*
 * ConstraintStmtExpr.h
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#ifndef SRC_CONSTRAINTS_CONSTRAINTSTMTEXPR_H_
#define SRC_CONSTRAINTS_CONSTRAINTSTMTEXPR_H_
#include "constraints/ConstraintStmt.h"
#include "expr/Expr.h"

namespace vsc {

class ConstraintStmtExpr : public ConstraintStmt {
public:
	ConstraintStmtExpr(Expr *expr);

	virtual ~ConstraintStmtExpr();

	Expr *expr() const { return m_expr.get(); }

	virtual void accept(IVisitor *v) { v->visitConstraintStmtExpr(this); }

private:
	ExprSP				m_expr;
};

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTSTMTEXPR_H_ */
