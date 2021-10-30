/*
 * ModelExprUnary.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"
#include "UnaryOp.h"

namespace vsc {

class ModelExprUnary : public ModelExpr {
public:
	ModelExprUnary(
			ModelExpr		*expr,
			UnaryOp			op
			);

	virtual ~ModelExprUnary();

	ModelExpr *expr() const { return m_expr.get(); }

	UnaryOp op() const { return m_op; }

	virtual void accept(IVisitor *v) override { v->visitModelExprUnary(this); }

private:
	ModelExprUP				m_expr;
	UnaryOp					m_op;

};

} /* namespace vsc */

