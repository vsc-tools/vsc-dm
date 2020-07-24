/*
 * ExprRangelist.h
 *
 *  Created on: Jul 23, 2020
 *      Author: ballance
 */

#pragma once
#include <vector>
#include "expr/Expr.h"
#include "expr/ExprRange.h"

namespace vsc {

class ExprRangelist : public Expr {
public:
	ExprRangelist();

	virtual ~ExprRangelist();

	void addRange(ExprRangeSP range);

	const std::vector<ExprRangeSP> ranges() const {
		return m_ranges;
	}

	virtual void accept(IVisitor *v) { v->visitExprRangelist(this); }

private:
	std::vector<ExprRangeSP>		m_ranges;
};

} /* namespace vsc */

