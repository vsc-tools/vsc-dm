/*
 * VisitorProxy.h
 *
 *  Created on: Feb 13, 2022
 *      Author: mballance
 */

#pragma once
#include <Python.h>
#include "vsc/IVisitor.h"

class VisitorProxy : public vsc::IVisitor {
public:
	VisitorProxy(PyObject *obj);

	virtual ~VisitorProxy();

	virtual void visitDataTypeInt(vsc::IDataTypeInt *t) { }

	virtual void visitDataTypeStruct(vsc::IDataTypeStruct *t) { }

	virtual void visitModelConstraint(vsc::IModelConstraint *c) { }

	virtual void visitModelConstraintBlock(vsc::IModelConstraintBlock *c) { }

	virtual void visitModelConstraintExpr(vsc::IModelConstraintExpr *c) { }

	virtual void visitModelConstraintIf(vsc::IModelConstraintIf *c) { }

	virtual void visitModelConstraintImplies(vsc::IModelConstraintImplies *c) { }

	virtual void visitModelConstraintScope(vsc::IModelConstraintScope *c) { }

	virtual void visitModelConstraintSoft(vsc::IModelConstraintSoft *c) { }

	virtual void visitModelCoverCross(vsc::ModelCoverCross *c) { }

	virtual void visitModelCovergroup(vsc::ModelCovergroup *c) { }

	virtual void visitModelCoverpoint(vsc::ModelCoverpoint *c) { }

	virtual void visitModelExprBin(vsc::IModelExprBin *e) override;

	virtual void visitModelExprCond(vsc::IModelExprCond *e) { }

	virtual void visitModelExprFieldRef(vsc::IModelExprFieldRef *e) { }

	virtual void visitModelExprIn(vsc::IModelExprIn *e) { }

	virtual void visitModelExprPartSelect(vsc::IModelExprPartSelect *e) { }

	virtual void visitModelExprRange(vsc::IModelExprRange *e) { }

	virtual void visitModelExprRangelist(vsc::IModelExprRangelist *e) { }

	virtual void visitModelExprRef(vsc::IModelExprRef *e) { }

	virtual void visitModelExprUnary(vsc::IModelExprUnary *e) { }

	virtual void visitModelExprVal(vsc::IModelExprVal *e) { }

	virtual void visitModelExprVecSubscript(vsc::IModelExprVecSubscript *e) { }

	virtual void visitModelField(vsc::IModelField *f) { }

	virtual void visitModelFieldRoot(vsc::ModelFieldRoot *f) { }

	virtual void visitModelFieldType(vsc::ModelFieldType *f) { }

	virtual void visitModelFieldVec(vsc::ModelFieldVec *f) { }

	virtual void visitModelFieldVecRoot(vsc::ModelFieldVecRoot *f) { }

	virtual void visitTypeField(vsc::TypeField *f) { }

private:
	PyObject				*m_obj;

};

