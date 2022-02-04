/*
 * ModelExprVecSubscript.h
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExprVecSubscript.h"

namespace vsc {

class ModelExprVecSubscript : public IModelExprVecSubscript {
public:
	ModelExprVecSubscript(
			IModelExpr		*expr,
			IModelExpr		*subscript
			);

	virtual ~ModelExprVecSubscript();

	virtual int32_t width() const override { return -1; }

	virtual IModelExpr *expr() const override { return m_expr.get(); }

	virtual IModelExpr *subscript() const override { return m_subscript.get(); }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprVecSubscript(this); }
private:
	IModelExprUP				m_expr;
	IModelExprUP				m_subscript;
};

} /* namespace vsc */

