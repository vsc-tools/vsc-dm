/*
 * PyVisitorProxy.h
 *
 *  Created on: Jul 19, 2020
 *      Author: ballance
 */

#pragma once
#include "vsc/impl/VisitorBase.h"

using namespace vsc;

class PyVisitorProxy : public VisitorBase {
public:
	PyVisitorProxy(struct PyVisitor *v);

	virtual ~PyVisitorProxy();

	virtual void visitExpr(int v);

	virtual void visitModelFieldRef(IModelFieldRef *f) override;

	virtual void visitModelFieldRefRoot(IModelFieldRef *f) override;

	virtual void visitModelFieldRefType(IModelFieldRef *f) override;

	virtual void visitModelFieldRoot(IModelFieldRoot *f) override;

	virtual void visitModelFieldType(IModelFieldType *f) override;

private:
	struct PyVisitor				*m_v;

};

