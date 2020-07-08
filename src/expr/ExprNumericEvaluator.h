/*
 * ExprEvaluator.h
 *
 *  Created on: Jul 8, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRNUMERICEVALUATOR_H_
#define SRC_EXPR_EXPRNUMERICEVALUATOR_H_
#include "VisitorBase.h"
#include "expr/ExprValNumeric.h"

namespace vsc {

class ExprNumericEvaluator : public VisitorBase {
public:
	ExprNumericEvaluator();

	virtual ~ExprNumericEvaluator();

	ExprValSP eval(Expr *e);

	ExprValNumericSP eval_num(Expr *e);

	virtual void visitExprBin(ExprBin *e) override;

	virtual void visitExprFieldRef(ExprFieldRef *e) override;

private:
	ExprValSP _eval(ExprSP e);

private:
	ExprValNumericSP			m_val;

};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRNUMERICEVALUATOR_H_ */
