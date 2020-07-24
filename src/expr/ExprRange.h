/*
 * ExprRange.h
 *
 *  Created on: Jul 23, 2020
 *      Author: ballance
 */

#pragma once
#include "Expr.h"

namespace vsc {

class ExprRange;
typedef std::shared_ptr<ExprRange> ExprRangeSP;

class ExprRange : public Expr {
public:
	ExprRange(
			ExprSP		lhs,
			ExprSP		rhs);

	virtual ~ExprRange();

	ExprSP lhs() const { return m_lhs; }

	ExprSP rhs() const { return m_rhs; }

	virtual void accept(IVisitor *v) { v->visitExprRange(this); }

	static ExprRangeSP toRange(ExprSP r) {
		return std::dynamic_pointer_cast<ExprRange>(r);
	}

private:
	ExprSP				m_lhs;
	ExprSP				m_rhs;
};


} /* namespace vsc */

