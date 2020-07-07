/*
 * ConstraintSoft.h
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#ifndef SRC_CONSTRAINTS_CONSTRAINTSOFT_H_
#define SRC_CONSTRAINTS_CONSTRAINTSOFT_H_
#include "ConstraintStmt.h"
#include "Expr.h"

namespace vsc {

class ConstraintSoft : public ConstraintStmt {
public:
	ConstraintSoft(Expr *expr);

	virtual ~ConstraintSoft();

	Expr *expr() const { return m_expr.get(); }

private:
	ExprSP				m_expr;
};

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTSOFT_H_ */
