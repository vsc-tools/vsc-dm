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

void VisitorProxy::visitDataTypeEnum(vsc::dm::IDataTypeEnum *t) {
	VisitorProxy_visitDataTypeEnum(m_obj, t);
}

void VisitorProxy::visitDataTypeInt(vsc::dm::IDataTypeInt *t) {
	VisitorProxy_visitDataTypeInt(m_obj, t);
}

void VisitorProxy::visitDataTypeStruct(vsc::dm::IDataTypeStruct *t) {
	VisitorProxy_visitDataTypeStruct(m_obj, t);
}

void VisitorProxy::visitModelConstraintBlock(vsc::dm::IModelConstraintBlock *c) {
	VisitorProxy_visitModelConstraintBlock(m_obj, c);
}

void VisitorProxy::visitModelConstraintExpr(vsc::dm::IModelConstraintExpr *c) {
	VisitorProxy_visitModelConstraintExpr(m_obj, c);
}

void VisitorProxy::visitModelConstraintIfElse(vsc::dm::IModelConstraintIfElse *c) {
	VisitorProxy_visitModelConstraintIfElse(m_obj, c);
}

void VisitorProxy::visitModelConstraintImplies(vsc::dm::IModelConstraintImplies *c) {
	VisitorProxy_visitModelConstraintImplies(m_obj, c);
}

void VisitorProxy::visitModelConstraintScope(vsc::dm::IModelConstraintScope *c) {
	VisitorProxy_visitModelConstraintScope(m_obj, c);
}

void VisitorProxy::visitModelExprBin(vsc::dm::IModelExprBin *e) {
	VisitorProxy_visitModelExprBin(m_obj, e);
}

void VisitorProxy::visitModelExprCond(vsc::dm::IModelExprCond *e) {
	VisitorProxy_visitModelExprCond(m_obj, e);
}

void VisitorProxy::visitModelExprFieldRef(vsc::dm::IModelExprFieldRef *e) {
	VisitorProxy_visitModelExprFieldRef(m_obj, e);
}

void VisitorProxy::visitModelExprIn(vsc::dm::IModelExprIn *e) {
	VisitorProxy_visitModelExprIn(m_obj, e);
}

void VisitorProxy::visitModelExprPartSelect(vsc::dm::IModelExprPartSelect *e) {
	VisitorProxy_visitModelExprPartSelect(m_obj, e);
}

void VisitorProxy::visitModelExprRange(vsc::dm::IModelExprRange *e) {
	VisitorProxy_visitModelExprRange(m_obj, e);
}

void VisitorProxy::visitModelExprRangelist(vsc::dm::IModelExprRangelist *e) {
	VisitorProxy_visitModelExprRangelist(m_obj, e);
}

void VisitorProxy::visitModelExprRef(vsc::dm::IModelExprRef *e) {
	VisitorProxy_visitModelExprRef(m_obj, e);
}

void VisitorProxy::visitModelExprUnary(vsc::dm::IModelExprUnary *e) {
	VisitorProxy_visitModelExprUnary(m_obj, e);
}

void VisitorProxy::visitModelExprVecSubscript(vsc::dm::IModelExprVecSubscript *e) {
	VisitorProxy_visitModelExprVecSubscript(m_obj, e);
}

void VisitorProxy::visitModelFieldRef(vsc::dm::IModelFieldRef *f) {
	VisitorProxy_visitModelFieldRef(m_obj, f);
}

void VisitorProxy::visitModelFieldRefRoot(vsc::dm::IModelFieldRef *f) {
	VisitorProxy_visitModelFieldRefRoot(m_obj, f);
}

void VisitorProxy::visitModelFieldRefType(vsc::dm::IModelFieldTypeRef *f) {
	VisitorProxy_visitModelFieldRefType(m_obj, f);
}

void VisitorProxy::visitModelFieldRoot(vsc::dm::IModelFieldRoot *f) {
	fprintf(stdout, "visitModelFieldRoot\n");
	VisitorProxy_visitModelFieldRoot(m_obj, f);
}

void VisitorProxy::visitModelFieldType(vsc::dm::IModelFieldType *f) {
	VisitorProxy_visitModelFieldType(m_obj, f);
}

void VisitorProxy::visitTypeConstraintBlock(vsc::dm::ITypeConstraintBlock *c) {
	VisitorProxy_visitTypeConstraintBlock(m_obj, c);
}

void VisitorProxy::visitTypeConstraintExpr(vsc::dm::ITypeConstraintExpr *c) {
	VisitorProxy_visitTypeConstraintExpr(m_obj, c);
}

void VisitorProxy::visitTypeConstraintIfElse(vsc::dm::ITypeConstraintIfElse *c) {
	VisitorProxy_visitTypeConstraintIfElse(m_obj, c);
}

void VisitorProxy::visitTypeConstraintImplies(vsc::dm::ITypeConstraintImplies *c) {
	VisitorProxy_visitTypeConstraintImplies(m_obj, c);
}

void VisitorProxy::visitTypeConstraintScope(vsc::dm::ITypeConstraintScope *c) {
	VisitorProxy_visitTypeConstraintScope(m_obj, c);
}

void VisitorProxy::visitTypeExprBin(vsc::dm::ITypeExprBin *e) {
	VisitorProxy_visitTypeExprBin(m_obj, e);
}

void VisitorProxy::visitTypeExprFieldRef(vsc::dm::ITypeExprFieldRef *e) {
	VisitorProxy_visitTypeExprFieldRef(m_obj, e);
}

void VisitorProxy::visitTypeExprRange(vsc::dm::ITypeExprRange *e) {
	VisitorProxy_visitTypeExprRange(m_obj, e);
}

void VisitorProxy::visitTypeExprRangelist(vsc::dm::ITypeExprRangelist *e) {
	VisitorProxy_visitTypeExprRangelist(m_obj, e);
}

void VisitorProxy::visitTypeExprVal(vsc::dm::ITypeExprVal *e) {
	VisitorProxy_visitTypeExprVal(m_obj, e);
}
