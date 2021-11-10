/*
 * ModelExprVecSubscript.h
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"

namespace vsc {

class ModelExprVecSubscript : public ModelExpr {
public:
	ModelExprVecSubscript(
			ModelExpr		*expr,
			ModelExpr		*subscript
			);

	virtual ~ModelExprVecSubscript();

	virtual int32_t width() const override { return -1; }

	ModelExpr *expr() const { return m_expr.get(); }

	ModelExpr *subscript() const { return m_subscript.get(); }

	virtual void accept(IVisitor *v) override { v->visitModelExprVecSubscript(this); }
private:
	ModelExprUP				m_expr;
	ModelExprUP				m_subscript;
};

} /* namespace vsc */

