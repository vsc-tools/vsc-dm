/*
 * ModelExprCond.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"

namespace vsc {

class ModelExprCond : public ModelExpr {
public:
	ModelExprCond(
			ModelExpr		*cond,
			ModelExpr		*true_e,
			ModelExpr		*false_e);

	virtual ~ModelExprCond();

	ModelExpr *cond() const { return m_cond.get(); }

	ModelExpr *true_e() const { return m_true_e.get(); }

	ModelExpr *false_e() const { return m_false_e.get(); }

	virtual void accept(IVisitor *v) override { v->visitModelExprCond(this); }

private:
	ModelExprUP				m_cond;
	ModelExprUP				m_true_e;
	ModelExprUP				m_false_e;
};

} /* namespace vsc */

