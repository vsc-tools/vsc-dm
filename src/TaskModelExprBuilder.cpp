/*
 * TaskModelExprBuilder.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "TaskModelExprBuilder.h"

namespace vsc {
namespace dm {

TaskModelExprBuilder::TaskModelExprBuilder(
		IContext		*ctxt,
		IModelField 	*scope) :
	m_ctxt(ctxt), m_scope(scope), m_expr(0) {

}

TaskModelExprBuilder::~TaskModelExprBuilder() {
	// TODO Auto-generated destructor stub
}

IModelExpr *TaskModelExprBuilder::build(ITypeExpr *e) {
	return expr(e);
}

void TaskModelExprBuilder::visitTypeExprBin(ITypeExprBin *e) {
	IModelExpr *lhs = expr(e->lhs());
	IModelExpr *rhs = expr(e->rhs());
	m_expr = m_ctxt->mkModelExprBin(lhs, e->op(), rhs);
}

void TaskModelExprBuilder::visitTypeExprFieldRef(ITypeExprFieldRef *e) {
	IModelField *f = 0;

    switch (e->getRootRefKind()) {
        case ITypeExprFieldRef::RootRefKind::TopDownScope: {
            f = m_scope;
        } break;
        case ITypeExprFieldRef::RootRefKind::BottomUpScope: {
            // ERROR;
        } break;
    }

	for (std::vector<int32_t>::const_iterator
        it=e->getPath().begin(); 
        it!=e->getPath().end(); it++) {
		f = m_scope->getField(*it);
	}

	m_expr = m_ctxt->mkModelExprFieldRef(f);
}

void TaskModelExprBuilder::visitTypeExprVal(ITypeExprVal *e) {
	m_expr = m_ctxt->mkModelExprVal(e->val());
}

void TaskModelExprBuilder::visitTypeField(ITypeField *f) {

}

IModelExpr *TaskModelExprBuilder::expr(ITypeExpr *e) {
	m_expr = 0;
	e->accept(this);
	return m_expr;
}

}
}

