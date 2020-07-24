/*
 * ExprValLiteral.h
 *
 *  Created on: Jul 23, 2020
 *      Author: ballance
 */

#pragma once
#include "Expr.h"
#include "ExprVal.h"

namespace vsc {

class ExprValLiteral {
public:
	ExprValLiteral(ExprVal *val);

	ExprValLiteral(ExprValSP val);

	virtual ~ExprValLiteral();

	ExprValSP val() const { return m_val; }

	virtual void accept(IVisitor *v) { v->visitExprValLiteral(this); }

private:
	ExprValSP				m_val;

};

}

