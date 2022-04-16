/*
 * TypeConstraintExpr.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeConstraintExpr.h"


namespace vsc {

class TypeConstraintExpr : public ITypeConstraintExpr {
public:
	TypeConstraintExpr(ITypeExpr *expr);

	virtual ~TypeConstraintExpr();

	virtual ITypeExpr *expr() const override {
		return m_expr.get();
	}

	virtual void accept(IVisitor *v) override { v->visitTypeConstraintExpr(this); }

private:
	ITypeExprUP					m_expr;

};

} /* namespace vsc */

