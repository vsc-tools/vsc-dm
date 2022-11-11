/*
 * VisitorProxy.cpp
 *
 *  Created on: Feb 13, 2022
 *      Author: mballance
 */

#include "VisitorProxy.h"
#include "core.h"

VisitorProxy::VisitorProxy(PyObject *obj) : VisitorBase(false), m_obj(obj) {
	Py_INCREF(m_obj);

}

VisitorProxy::~VisitorProxy() {
	Py_DECREF(m_obj);
}

void VisitorProxy::visitDataTypeEnum(vsc::IDataTypeEnum *t) {
	VisitorProxy_visitDataTypeEnum(m_obj, t);
}

void VisitorProxy::visitDataTypeInt(vsc::IDataTypeInt *t) {
	VisitorProxy_visitDataTypeInt(m_obj, t);
}

void VisitorProxy::visitDataTypeStruct(vsc::IDataTypeStruct *t) {
	VisitorProxy_visitDataTypeStruct(m_obj, t);
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

void VisitorProxy::visitModelExprCond(vsc::IModelExprCond *e) {
	VisitorProxy_visitModelExprCond(m_obj, e);
}

void VisitorProxy::visitModelExprFieldRef(vsc::IModelExprFieldRef *e) {
	VisitorProxy_visitModelExprFieldRef(m_obj, e);
}

void VisitorProxy::visitModelExprIn(vsc::IModelExprIn *e) {
	VisitorProxy_visitModelExprIn(m_obj, e);
}

void VisitorProxy::visitModelExprPartSelect(vsc::IModelExprPartSelect *e) {
	VisitorProxy_visitModelExprPartSelect(m_obj, e);
}

void VisitorProxy::visitModelExprRange(vsc::IModelExprRange *e) {
	VisitorProxy_visitModelExprRange(m_obj, e);
}

void VisitorProxy::visitModelExprRangelist(vsc::IModelExprRangelist *e) {
	VisitorProxy_visitModelExprRangelist(m_obj, e);
}

void VisitorProxy::visitModelExprRef(vsc::IModelExprRef *e) {
	VisitorProxy_visitModelExprRef(m_obj, e);
}

void VisitorProxy::visitModelExprUnary(vsc::IModelExprUnary *e) {
	VisitorProxy_visitModelExprUnary(m_obj, e);
}

void VisitorProxy::visitModelExprVal(vsc::IModelExprVal *e) {
	VisitorProxy_visitModelExprVal(m_obj, e);
}

void VisitorProxy::visitModelExprVecSubscript(vsc::IModelExprVecSubscript *e) {
	VisitorProxy_visitModelExprVecSubscript(m_obj, e);
}

void VisitorProxy::visitModelFieldRef(vsc::IModelFieldRef *f) {
	VisitorProxy_visitModelFieldRef(m_obj, f);
}

void VisitorProxy::visitModelFieldRefRoot(vsc::IModelFieldRef *f) {
	VisitorProxy_visitModelFieldRefRoot(m_obj, f);
}

void VisitorProxy::visitModelFieldRefType(vsc::IModelFieldTypeRef *f) {
	VisitorProxy_visitModelFieldRefType(m_obj, f);
}

void VisitorProxy::visitModelFieldRoot(vsc::IModelFieldRoot *f) {
	fprintf(stdout, "visitModelFieldRoot\n");
	VisitorProxy_visitModelFieldRoot(m_obj, f);
}

void VisitorProxy::visitModelFieldType(vsc::IModelFieldType *f) {
	VisitorProxy_visitModelFieldType(m_obj, f);
}

void VisitorProxy::visitTypeConstraintBlock(vsc::ITypeConstraintBlock *c) {
	VisitorProxy_visitTypeConstraintBlock(m_obj, c);
}

void VisitorProxy::visitTypeConstraintExpr(vsc::ITypeConstraintExpr *c) {
	VisitorProxy_visitTypeConstraintExpr(m_obj, c);
}

void VisitorProxy::visitTypeConstraintIfElse(vsc::ITypeConstraintIfElse *c) {
	VisitorProxy_visitTypeConstraintIfElse(m_obj, c);
}

void VisitorProxy::visitTypeConstraintImplies(vsc::ITypeConstraintImplies *c) {
	VisitorProxy_visitTypeConstraintImplies(m_obj, c);
}

void VisitorProxy::visitTypeConstraintScope(vsc::ITypeConstraintScope *c) {
	VisitorProxy_visitTypeConstraintScope(m_obj, c);
}

void VisitorProxy::visitTypeExprBin(vsc::ITypeExprBin *e) {
	VisitorProxy_visitTypeExprBin(m_obj, e);
}

void VisitorProxy::visitTypeExprFieldRef(vsc::ITypeExprFieldRef *e) {
	VisitorProxy_visitTypeExprFieldRef(m_obj, e);
}

void VisitorProxy::visitTypeExprRange(vsc::ITypeExprRange *e) {
	VisitorProxy_visitTypeExprRange(m_obj, e);
}

void VisitorProxy::visitTypeExprRangelist(vsc::ITypeExprRangelist *e) {
	VisitorProxy_visitTypeExprRangelist(m_obj, e);
}

void VisitorProxy::visitTypeExprVal(vsc::ITypeExprVal *e) {
	VisitorProxy_visitTypeExprVal(m_obj, e);
}
