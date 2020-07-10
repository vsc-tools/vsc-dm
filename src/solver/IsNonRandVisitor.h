/*
 * IsNonRandVisitor.h
 *
 *  Created on: Jul 9, 2020
 *      Author: ballance
 */

#pragma once
#include "VisitorBase.h"
#include "expr/Expr.h"

namespace vsc {

// Evaluates the specified expression to determine whether the
// expression contains any non-random field references
class IsNonRandVisitor : public VisitorBase {
public:
	IsNonRandVisitor();

	virtual ~IsNonRandVisitor();

	bool is_nonrand(const ExprSP &expr);

	virtual void visitExprFieldRef(ExprFieldRef *e) override;

private:
	bool				m_is_nonrand;

};

} /* namespace vsc */

