/*
 * ModelExprUnary.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExprUnary.h"

namespace vsc {

class ModelExprUnary : public IModelExprUnary {
public:
	ModelExprUnary(
			IModelExpr		*expr,
			UnaryOp			op
			);

	virtual ~ModelExprUnary();

	virtual IModelExpr *expr() const override { return m_expr.get(); }

	virtual UnaryOp op() const override { return m_op; }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprUnary(this); }

private:
	IModelExprUP			m_expr;
	UnaryOp					m_op;

};

} /* namespace vsc */

