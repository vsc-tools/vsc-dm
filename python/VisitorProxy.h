/*
 * VisitorProxy.h
 *
 *  Created on: Feb 13, 2022
 *      Author: mballance
 */

#pragma once
#include <Python.h>
#include "vsc/IVisitor.h"
#include "vsc/IModelExprBin.h"

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

    void visitModelExprBinBase(vsc::IModelExprBin *e);

	virtual void visitModelExprCond(vsc::IModelExprCond *e) override;

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

	virtual void visitModelFieldRoot(vsc::IModelFieldRoot *f) { }

	virtual void visitModelFieldType(vsc::IModelFieldType *f) { }

	virtual void visitModelFieldVec(vsc::IModelFieldVec *f) { }

	virtual void visitModelFieldVecRoot(vsc::IModelFieldVecRoot *f) { }

	virtual void visitTypeConstraintBlock(vsc::ITypeConstraintBlock *c) override { }

	virtual void visitTypeConstraintExpr(vsc::ITypeConstraintExpr *c) override { }

	virtual void visitTypeConstraintScope(vsc::ITypeConstraintScope *c) override { }


	virtual void visitTypeExprBin(vsc::ITypeExprBin *e) override { }

	virtual void visitTypeExprFieldRef(vsc::ITypeExprFieldRef *e) override { }

	virtual void visitTypeExprVal(vsc::ITypeExprVal *e) override { }

	virtual void visitTypeField(vsc::ITypeField *f) { }

private:
	PyObject				*m_obj;

};

