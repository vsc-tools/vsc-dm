/*
 * VisitorProxy.cpp
 *
 *  Created on: Feb 13, 2022
 *      Author: mballance
 */

#include "VisitorProxy.h"
#include "core.h"

VisitorProxy::VisitorProxy(PyObject *obj) : m_obj(obj) {
	// TODO Auto-generated constructor stub

}

VisitorProxy::~VisitorProxy() {
	// TODO Auto-generated destructor stub
}

void VisitorProxy::visitModelExprBin(vsc::IModelExprBin *e) {
	VisitorProxy_visitModelExprBin(m_obj, e);
}


