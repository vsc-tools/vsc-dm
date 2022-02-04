/*
 * ModelExprRange.h
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExprRange.h"

namespace vsc {

class ModelExprRange;
using ModelExprRangeUP=std::unique_ptr<ModelExprRange>;
class ModelExprRange : public IModelExprRange {
public:
	ModelExprRange(
			IModelExpr		*lower,
			IModelExpr		*upper);

	virtual ~ModelExprRange();

	virtual int32_t width() const override;

	virtual IModelExpr *lower() const override { return m_lower.get(); }

	virtual IModelExpr *upper() const override { return m_upper.get(); }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprRange(this); }

private:
	IModelExprUP			m_lower;
	IModelExprUP			m_upper;
};

} /* namespace vsc */

