/*
 * ExprUnary.h
 *
 *  Created on: Jul 23, 2020
 *      Author: ballance
 */

#pragma once
#include "expr/Expr.h"
#include "expr/ExprUnaryOp.h"

namespace vsc {

class ExprUnary : public Expr {
public:
	ExprUnary(
			ExprUnaryOp		op,
			ExprSP			rhs);

	virtual ~ExprUnary();

	ExprUnaryOp op() const { return m_op; }

	ExprSP rhs() const { return m_rhs; }

	virtual void accept(IVisitor *v) { v->visitExprUnary(this); }

private:
	ExprUnaryOp				m_op;
	ExprSP					m_rhs;
};

}

