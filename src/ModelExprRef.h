/*
 * ModelExprRef.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExprRef.h"
#include "ModelExpr.h"

namespace vsc {
namespace dm {

class ModelExprRef : public virtual IModelExprRef, public virtual ModelExpr {
public:
	ModelExprRef(IModelExpr *expr);

	virtual ~ModelExprRef();

	virtual int32_t width() { return m_expr->width(); }

	virtual void eval(IModelVal *dst) override { }

	virtual IModelExpr *expr() const override { return m_expr; }

	virtual void accept(IVisitor *v) override { v->visitModelExprRef(this); }

private:
	IModelExpr				*m_expr;
};

}
} /* namespace vsc */

