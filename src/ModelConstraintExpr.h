/*
 * ModelConstraintExpr.h
 *
 *  Created on: Oct 8, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelConstraint.h"
#include "ModelExpr.h"

namespace vsc {

class ModelConstraintExpr;
using ModelConstraintExprUP=std::unique_ptr<ModelConstraintExpr>;
class ModelConstraintExpr : public ModelConstraint {
public:
	ModelConstraintExpr(ModelExpr *expr);

	virtual ~ModelConstraintExpr();

	ModelExpr *expr() const { return m_expr.get(); }

	virtual void accept(IVisitor *v) override { v->visitModelConstraintExpr(this); }

private:
	ModelExprUP						m_expr;

};

} /* namespace vsc */

