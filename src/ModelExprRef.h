/*
 * ModelExprRef.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExprRef.h"

namespace vsc {

class ModelExprRef : public IModelExprRef {
public:
	ModelExprRef(IModelExpr *expr);

	virtual ~ModelExprRef();

	virtual IModelExpr *expr() const override { return m_expr; }

	virtual void accept(IVisitor *v) override { v->visitModelExprRef(this); }

private:
	IModelExpr				*m_expr;
};

} /* namespace vsc */

