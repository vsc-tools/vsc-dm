/*
 * ModelExprCond.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExprCond.h"
#include "ModelExpr.h"

namespace vsc {

class ModelExprCond : public IModelExprCond {
public:
	ModelExprCond(
			IModelExpr		*cond,
			IModelExpr		*true_e,
			IModelExpr		*false_e);

	virtual ~ModelExprCond();

	virtual IModelExpr *getCond() const override {
		return m_cond.get();
	}

	virtual IModelExpr *getTrue() const override {
		return m_true_e.get();
	}

	virtual IModelExpr *getFalse() const override {
		return m_false_e.get();
	}

	virtual void accept(IVisitor *v) override { v->visitModelExprCond(this); }

private:
	IModelExprUP				m_cond;
	IModelExprUP				m_true_e;
	IModelExprUP				m_false_e;
};

} /* namespace vsc */

