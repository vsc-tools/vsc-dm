/*
 * ModelExprRange.h
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"

namespace vsc {

class ModelExprRange;
using ModelExprRangeUP=std::unique_ptr<ModelExprRange>;
class ModelExprRange : public ModelExpr {
public:
	ModelExprRange(
			ModelExpr		*lower,
			ModelExpr		*upper);

	virtual ~ModelExprRange();

	ModelExpr *lower() const { return m_lower.get(); }

	ModelExpr *upper() const { return m_upper.get(); }

	virtual void accept(IVisitor *v) override { v->visitModelExprRange(this); }

private:
	ModelExprUP			m_lower;
	ModelExprUP			m_upper;
};

} /* namespace vsc */

