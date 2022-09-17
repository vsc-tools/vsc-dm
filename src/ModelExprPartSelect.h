/*
 * ModelExprPartSelect.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelExpr.h"
#include "vsc/IModelExprPartSelect.h"

namespace vsc {

class ModelExprPartSelect : public IModelExprPartSelect {
public:
	ModelExprPartSelect(
			IModelExpr			*lhs,
			int32_t				upper,
			int32_t				lower
			);

	virtual ~ModelExprPartSelect();

	virtual IModelExpr *lhs() const override { return m_lhs.get(); }

	virtual int32_t lower() const override { return m_lower; }

	virtual int32_t upper() const override { return m_upper; }

	virtual int32_t width() override { return m_upper-m_lower+1; }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) { v->visitModelExprPartSelect(this); }

private:
	IModelExprUP				m_lhs;
	int32_t						m_upper;
	int32_t						m_lower;
};

} /* namespace vsc */

