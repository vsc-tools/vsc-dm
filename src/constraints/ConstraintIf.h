/*
 * ConstraintIf.h
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#ifndef SRC_CONSTRAINTS_CONSTRAINTIF_H_
#define SRC_CONSTRAINTS_CONSTRAINTIF_H_
#include "constraints/ConstraintStmt.h"
#include "expr/Expr.h"

namespace vsc {

class ConstraintIf : public ConstraintStmt {

public:
	ConstraintIf(
			Expr			*cond,
			ConstraintStmt	*true_s,
			ConstraintStmt	*false_s);

	ConstraintIf(
			ExprSP				cond,
			ConstraintStmtSP	true_s,
			ConstraintStmtSP	false_s);

	virtual ~ConstraintIf();

	Expr *cond() const { return m_cond.get(); }

	ConstraintStmt *true_s() const { return m_true_s.get(); }

	ConstraintStmt *false_s() const { return m_false_s.get(); }

	virtual void accept(IVisitor *v) { v->visitConstraintIf(this); }

private:
	ExprSP					m_cond;
	ConstraintStmtSP		m_true_s;
	ConstraintStmtSP		m_false_s;
};

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTIF_H_ */
