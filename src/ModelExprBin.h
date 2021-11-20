/*
 * ModelExprBin.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once
#include "BinOp.h"
#include "ModelExpr.h"
#include "ModelVal.h"

namespace vsc {

class ModelExprBin : public ModelExpr {
public:
	ModelExprBin(
			ModelExpr			*lhs,
			BinOp				op,
			ModelExpr			*rhs);

	virtual ~ModelExprBin();

	virtual int32_t width() const override { return m_width; }

	ModelExpr *lhs() const { return m_lhs.get(); }

	BinOp op() const { return m_op; }

	ModelExpr *rhs() const { return m_rhs.get(); }

	virtual void eval(ModelVal &dst) override;

	virtual void accept(IVisitor *v) { v->visitModelExprBin(this); }

private:
	static void eq_op_64(ModelVal &dst, const ModelVal &op1, const ModelVal &op2);

private:
	ModelExprUP					m_lhs;
	BinOp						m_op;
	ModelExprUP					m_rhs;
	int32_t						m_width;
	bool						m_signed;
};

} /* namespace vsc */

