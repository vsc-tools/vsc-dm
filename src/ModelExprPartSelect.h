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

	virtual void accept(IVisitor *v) { v->visitModelExprPartSelect(this); }

private:
	ModelExprUP					m_lhs;
	int32_t						m_upper;
	int32_t						m_lower;
};

} /* namespace vsc */

