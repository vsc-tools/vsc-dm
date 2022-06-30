/*
 * PyVisitorProxy.cpp
 *
 *  Created on: Jul 19, 2020
 *      Author: ballance
 */

#include "PyVisitorProxy.h"
#include "core.h"

PyVisitorProxy::PyVisitorProxy(PyVisitor *v) : m_v(v) {
	Py_INCREF(m_v);

}

PyVisitorProxy::~PyVisitorProxy() {
	Py_DECREF(m_v);
}

void PyVisitorProxy::visitExpr(int v) {
	Visitor_visitExpr(m_v, v);
}

void PyVisitorProxy::visitModelFieldRef(IModelFieldRef *f) {
	Visitor_visitModelFieldRef(m_v, f);
}

void PyVisitorProxy::visitModelFieldRefRoot(IModelFieldRef *f) {
	Visitor_visitModelFieldRefRoot(m_v, f);
}

void PyVisitorProxy::visitModelFieldRefType(IModelFieldRef *f) {
	Visitor_visitModelFieldRefType(m_v, f);
}

void PyVisitorProxy::visitModelFieldRoot(IModelFieldRoot *f) {
	fprintf(stdout, "visitModelFieldRoot\n");
	Visitor_visitModelFieldRoot(m_v, f);
}

void PyVisitorProxy::visitModelFieldType(IModelFieldType *f) {
	Visitor_visitModelFieldType(m_v, f);
}

