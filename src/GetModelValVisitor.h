/*
 * GetModelValVisitor.h
 *
 *  Created on: Nov 8, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

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

}
} /* namespace vsc */

