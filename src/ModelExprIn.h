/*
 * ModelExprIn.h
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExprIn.h"
#include "ModelExprRangelist.h"

namespace vsc {

class ModelExprIn : public IModelExprIn {
public:
	ModelExprIn(
			IModelExpr			*lhs,
			IModelExprRangelist	*rangelist);

	virtual ~ModelExprIn();

	virtual int32_t width() override { return 1; }

	virtual IModelExpr *lhs() const override { return m_lhs.get(); }

	virtual IModelExprRangelist *rangelist() const override { return m_rangelist.get(); }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprIn(this); }

private:
	IModelExprUP					m_lhs;
	IModelExprRangelistUP			m_rangelist;

};

} /* namespace vsc */

