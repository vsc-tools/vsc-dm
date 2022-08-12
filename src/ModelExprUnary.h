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
			UnaryOp			op,
			IModelExpr		*expr
			);

	virtual ~ModelExprUnary();

	virtual int32_t width() const { return m_width; }

	virtual IModelExpr *expr() const override { return m_expr.get(); }

	virtual UnaryOp op() const override { return m_op; }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprUnary(this); }

private:
	int32_t					m_width;
	IModelExprUP			m_expr;
	UnaryOp					m_op;

};

} /* namespace vsc */

