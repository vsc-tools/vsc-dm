/*
 * GetModelValVisitor.h
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/impl/VisitorBase.h"

namespace vsc {

class GetModelValVisitor : public VisitorBase {
public:
	GetModelValVisitor();

	virtual ~GetModelValVisitor();

	IModelVal *value(
			IModelField		*ctx,
			IModelExpr		*expr);

	virtual void visitModelExprVecSubscript(IModelExprVecSubscript *e) override;

private:
	IModelField				*m_ctx;
	IModelExpr				*m_expr;
	IModelVal				*m_val;
};

} /* namespace vsc */

