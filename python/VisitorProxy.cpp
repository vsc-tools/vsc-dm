/*
 * VisitorProxy.cpp
 *
 *  Created on: Feb 13, 2022
 *      Author: mballance
 */

#include "VisitorProxy.h"
#include "core.h"

VisitorProxy::VisitorProxy(PyObject *obj) : m_obj(obj) {
	Py_INCREF(m_obj);

}

VisitorProxy::~VisitorProxy() {
	Py_DECREF(m_obj);
}

void VisitorProxy::visitModelConstraintBlock(vsc::IModelConstraintBlock *c) {
	VisitorProxy_visitModelConstraintBlock(m_obj, c);
}

void VisitorProxy::visitModelConstraintExpr(vsc::IModelConstraintExpr *c) {
	VisitorProxy_visitModelConstraintExpr(m_obj, c);
}

void VisitorProxy::visitModelConstraintIfElse(vsc::IModelConstraintIfElse *c) {
	VisitorProxy_visitModelConstraintIfElse(m_obj, c);
}

void VisitorProxy::visitModelConstraintImplies(vsc::IModelConstraintImplies *c) {
	VisitorProxy_visitModelConstraintImplies(m_obj, c);
}

void VisitorProxy::visitModelConstraintScope(vsc::IModelConstraintScope *c) {
	VisitorProxy_visitModelConstraintScope(m_obj, c);
}

void VisitorProxy::visitModelExprBin(vsc::IModelExprBin *e) {
	VisitorProxy_visitModelExprBin(m_obj, e);
}

void VisitorProxy::visitModelExprBinBase(vsc::IModelExprBin *e) {
	e->lhs()->accept(this);
	e->rhs()->accept(this);
}

void VisitorProxy::visitModelExprCond(vsc::IModelExprCond *e) {
//	VisitorProxy_visitModelExprCond(e);
}

void VisitorProxy::visitModelFieldRef(vsc::IModelFieldRef *f) {
	VisitorProxy_visitModelFieldRef(m_obj, f);
}

void VisitorProxy::visitModelFieldRefRoot(vsc::IModelFieldRef *f) {
	VisitorProxy_visitModelFieldRefRoot(m_obj, f);
}

void VisitorProxy::visitModelFieldRefType(vsc::IModelFieldRef *f) {
	VisitorProxy_visitModelFieldRefType(m_obj, f);
}

void VisitorProxy::visitModelFieldRoot(vsc::IModelFieldRoot *f) {
	fprintf(stdout, "visitModelFieldRoot\n");
	VisitorProxy_visitModelFieldRoot(m_obj, f);
}

void VisitorProxy::visitModelFieldType(vsc::IModelFieldType *f) {
	VisitorProxy_visitModelFieldType(m_obj, f);
}

