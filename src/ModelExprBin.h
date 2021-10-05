/*
 * ModelExprBin.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once
#include "BinOp.h"
#include "ModelExpr.h"

namespace vsc {

class ModelExprBin : public ModelExpr {
public:
	ModelExprBin(
			ModelExpr			*lhs,
			BinOp				op,
			ModelExpr			*rhs);

	virtual ~ModelExprBin();

	ModelExpr *lhs() const { return m_lhs.get(); }

	BinOp op() const { return m_op; }

	ModelExpr *rhs() const { return m_rhs.get(); }

	virtual void accept(IVisitor *v) { v->visitModelExprBin(this); }

private:
	ModelExprUP					m_lhs;
	BinOp						m_op;
	ModelExprUP					m_rhs;
};

} /* namespace vsc */

