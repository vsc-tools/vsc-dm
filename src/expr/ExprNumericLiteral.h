/*
 * ExprNumericLiteral.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRNUMERICLITERAL_H_
#define SRC_EXPR_EXPRNUMERICLITERAL_H_
#include "expr/Expr.h"

namespace vsc {

class ExprNumericLiteral : public Expr {
public:
	ExprNumericLiteral(uint64_t	val);

	virtual ~ExprNumericLiteral();

	virtual void accept(IVisitor *v) { v->visitExprNumericLiteral(this); }

private:
	uint64_t				m_val;

};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRNUMERICLITERAL_H_ */
