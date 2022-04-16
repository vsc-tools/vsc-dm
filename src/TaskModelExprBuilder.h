/*
 * TaskModelExprBuilder.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IContext.h"
#include "VisitorBase.h"

namespace vsc {

class TaskModelExprBuilder : public VisitorBase {
public:
	TaskModelExprBuilder(
			IContext		*ctxt,
			IModelField 	*scope);

	virtual ~TaskModelExprBuilder();

	IModelExpr *build(ITypeExpr *expr);

	virtual void visitTypeExprBin(ITypeExprBin *e) override;

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) override;

	virtual void visitTypeExprVal(ITypeExprVal *e) override;

	virtual void visitTypeField(ITypeField *f) override;

private:
	IModelExpr *expr(ITypeExpr *expr);

private:
	IContext					*m_ctxt;
	IModelField					*m_scope;
	IModelExpr					*m_expr;

};

}


