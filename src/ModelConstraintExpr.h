/*
 * ModelConstraintExpr.h
 *
 *  Created on: Oct 8, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExpr.h"
#include "vsc/IModelConstraintExpr.h"
#include "ModelConstraint.h"

namespace vsc {

class ModelConstraintExpr;
using ModelConstraintExprUP=std::unique_ptr<ModelConstraintExpr>;
class ModelConstraintExpr : 
	public virtual IModelConstraintExpr,
	public virtual ModelConstraint {
public:
	ModelConstraintExpr(IModelExpr *expr);

	virtual ~ModelConstraintExpr();

	virtual IModelExpr *expr() const override {
		return m_expr.get();
	}

	virtual void accept(IVisitor *v) override { v->visitModelConstraintExpr(this); }

private:
	IModelExprUP						m_expr;

};

} /* namespace vsc */

