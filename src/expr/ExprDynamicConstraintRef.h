/*
 * ExprDynamicConstraintRef.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRDYNAMICCONSTRAINTREF_H_
#define SRC_EXPR_EXPRDYNAMICCONSTRAINTREF_H_
#include "Expr.h"
#include "ConstraintBlock.h"

namespace vsc {

class ExprDynamicConstraintRef : public Expr {
public:
	ExprDynamicConstraintRef(
			ConstraintBlock			*constraint);

	virtual ~ExprDynamicConstraintRef();

	ConstraintBlock *constraint() const { return m_constraint.get(); }

	virtual void accept(IVisitor *v) { v->visitExprDynamicConstraintRef(this); }

private:
	ConstraintBlockSP				m_constraint;

};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRDYNAMICCONSTRAINTREF_H_ */
