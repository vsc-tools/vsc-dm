/*
 * ModelExprPartSelect.h
 *
 *  Created on: Oct 29, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"

namespace vsc {

class ModelExprPartSelect : public ModelExpr {
public:
	ModelExprPartSelect(
			ModelExpr			*lhs,
			int32_t				upper,
			int32_t				lower
			);

	virtual ~ModelExprPartSelect();

	ModelExpr *lhs() const { return m_lhs.get(); }

	int32_t lower() const { return m_lower; }

	int32_t upper() const { return m_upper; }

	virtual int32_t width() const override { return m_upper-m_lower+1; }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) { v->visitModelExprPartSelect(this); }

private:
	ModelExprUP					m_lhs;
	int32_t						m_upper;
	int32_t						m_lower;
};

} /* namespace vsc */

