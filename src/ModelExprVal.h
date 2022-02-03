/*
 * ModelExprVal.h
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"
#include "ModelVal.h"

namespace vsc {

class ModelExprVal : public ModelExpr {
public:
	ModelExprVal();

	ModelExprVal(const ModelVal &val);

	virtual ~ModelExprVal();

	virtual int32_t width() const override { return m_val.bits(); }

	const ModelVal &val() const { return m_val; }

	ModelVal &val() { return m_val; }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprVal(this); }

private:
	ModelVal			m_val;
};

} /* namespace vsc */

