/*
 * ModelExprRange.h
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExprRange.h"

namespace vsc {
namespace dm {

class ModelExprRange;
using ModelExprRangeUP=std::unique_ptr<ModelExprRange>;
class ModelExprRange : public IModelExprRange {
public:
	ModelExprRange(
			bool			is_single,
			IModelExpr		*lower,
			IModelExpr		*upper);

	virtual ~ModelExprRange();

	virtual int32_t width() override;

	virtual bool isSingle() const override { return m_is_single; }

	virtual IModelExpr *lower() const override { return m_lower.get(); }

	virtual IModelExpr *upper() const override { return m_upper.get(); }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprRange(this); }

private:
	bool					m_is_single;
	IModelExprUP			m_lower;
	IModelExprUP			m_upper;
};

}
} /* namespace vsc */

