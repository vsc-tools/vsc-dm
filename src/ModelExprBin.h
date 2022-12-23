/*
 * ModelExprBin.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExprBin.h"
#include "vsc/dm/BinOp.h"
#include "ModelExpr.h"
#include "ModelVal.h"

namespace vsc {
namespace dm {

class ModelExprBin : public IModelExprBin {
public:
	ModelExprBin(
			IModelExpr			*lhs,
			BinOp				op,
			IModelExpr			*rhs);

	virtual ~ModelExprBin();

	virtual int32_t width() override { return m_width; }

	virtual IModelExpr *lhs() const override { return m_lhs.get(); }

	virtual BinOp op() const override { return m_op; }

	virtual IModelExpr *rhs() const override { return m_rhs.get(); }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprBin(this); }

private:
	static void eq_op_64(IModelVal *dst, const ModelVal &op1, const ModelVal &op2);

private:
	IModelExprUP				m_lhs;
	BinOp						m_op;
	IModelExprUP				m_rhs;
	int32_t						m_width;
	bool						m_signed;
};

}
} /* namespace vsc */

