/*
 * ModelExprVal.h
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExprVal.h"
#include "ModelVal.h"

namespace vsc {

class ModelExprVal : public IModelExprVal {
public:
	ModelExprVal();

	ModelExprVal(const IModelVal *val);

	ModelExprVal(const IModelVal &val);

	virtual ~ModelExprVal();

	virtual int32_t width() const override { return m_val.bits(); }

	virtual const IModelVal *val() const override { return &m_val; }

	virtual IModelVal *val() { return &m_val; }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprVal(this); }

private:
	ModelVal			m_val;
};

} /* namespace vsc */

