/*
 * GetModelValVisitor.h
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#pragma once
#include "VisitorBase.h"

namespace vsc {

class GetModelValVisitor : public VisitorBase {
public:
	GetModelValVisitor();

	virtual ~GetModelValVisitor();

	ModelVal value(
			ModelField		*ctx,
			ModelExpr		*expr);

	virtual void visitModelExprVecSubscript(IModelExprVecSubscript *e) override;

private:
	ModelField				*m_ctx;
	ModelExpr				*m_expr;
	ModelVal				m_val;
};

} /* namespace vsc */

