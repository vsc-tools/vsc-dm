/*
 * PyVisitorProxy.h
 *
 *  Created on: Jul 19, 2020
 *      Author: ballance
 */

#pragma once
#include "../src/VisitorBase.h"

using namespace vsc;

class PyVisitorProxy : public VisitorBase {
public:
	PyVisitorProxy(struct PyVisitor *v);

	virtual ~PyVisitorProxy();

	virtual void visitExpr(int v);

private:
	struct PyVisitor				*m_v;

};

