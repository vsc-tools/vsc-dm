/*
 * ModelExprRef.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"

namespace vsc {

class ModelExprRef : public ModelExpr {
public:
	ModelExprRef(ModelExpr *expr);

	virtual ~ModelExprRef();

	ModelExpr *expr() const { return m_expr; }

	virtual void accept(IVisitor *v) override { v->visitModelExprRef(this); }

private:
	ModelExpr				*m_expr;
};

} /* namespace vsc */

