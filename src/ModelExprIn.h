/*
 * ModelExprIn.h
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"
#include "ModelExprRangelist.h"

namespace vsc {

class ModelExprIn : public ModelExpr {
public:
	ModelExprIn(
			ModelExpr			*lhs,
			ModelExprRangelist	*rangelist);

	virtual ~ModelExprIn();

	virtual int32_t width() const override { return 1; }

	ModelExpr *lhs() const { return m_lhs.get(); }

	ModelExprRangelist *rangelist() const { return m_rangelist.get(); }

	virtual void accept(IVisitor *v) override { v->visitModelExprIn(this); }

private:
	ModelExprUP					m_lhs;
	ModelExprRangelistUP		m_rangelist;

};

} /* namespace vsc */

