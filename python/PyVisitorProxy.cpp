/*
 * PyVisitorProxy.cpp
 *
 *  Created on: Jul 19, 2020
 *      Author: ballance
 */

#include "PyVisitorProxy.h"
#include "libvsc.h"

PyVisitorProxy::PyVisitorProxy(PyVisitor *v) : m_v(v) {
	// TODO Auto-generated constructor stub

}

PyVisitorProxy::~PyVisitorProxy() {
	// TODO Auto-generated destructor stub
}

void PyVisitorProxy::visitExpr(int v) {
	Visitor_visitExpr(m_v, v);
}

