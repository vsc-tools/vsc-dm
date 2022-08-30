/*
 * VisitorProxy.h
 *
 *  Created on: Feb 13, 2022
 *      Author: mballance
 */

#pragma once
#include <Python.h>
#include "vsc/impl/VisitorBase.h"
#include "vsc/IModelExprBin.h"

class VisitorProxy : public vsc::VisitorBase {
public:
	VisitorProxy(PyObject *obj);

	virtual ~VisitorProxy();

	virtual void visitDataTypeEnum(vsc::IDataTypeEnum *t) override;

	virtual void visitDataTypeInt(vsc::IDataTypeInt *t) override;

	virtual void visitDataTypeStruct(vsc::IDataTypeStruct *t) override;

#ifdef UNDEFINED
	virtual void visitModelConstraint(vsc::IModelConstraint *c) { }
#endif

	virtual void visitModelConstraintBlock(vsc::IModelConstraintBlock *c) override;

	virtual void visitModelConstraintExpr(vsc::IModelConstraintExpr *c) override;

	virtual void visitModelConstraintIfElse(vsc::IModelConstraintIfElse *c) override;

	virtual void visitModelConstraintImplies(vsc::IModelConstraintImplies *c) override;

	virtual void visitModelConstraintScope(vsc::IModelConstraintScope *c) override;

#ifdef UNDEFINED

	virtual void visitModelConstraintSoft(vsc::IModelConstraintSoft *c) { }

	virtual void visitModelCoverCross(vsc::ModelCoverCross *c) { }

	virtual void visitModelCovergroup(vsc::ModelCovergroup *c) { }

	virtual void visitModelCoverpoint(vsc::ModelCoverpoint *c) { }
#endif

	virtual void visitModelExprBin(vsc::IModelExprBin *e) override;

	virtual void visitModelExprCond(vsc::IModelExprCond *e) override;

	virtual void visitModelExprFieldRef(vsc::IModelExprFieldRef *e) override;

	virtual void visitModelExprIn(vsc::IModelExprIn *e) override;

	virtual void visitModelExprPartSelect(vsc::IModelExprPartSelect *e) override;

	virtual void visitModelExprRange(vsc::IModelExprRange *e) override;

	virtual void visitModelExprRangelist(vsc::IModelExprRangelist *e) override;

	virtual void visitModelExprRef(vsc::IModelExprRef *e) override;

	virtual void visitModelExprUnary(vsc::IModelExprUnary *e) override;

	virtual void visitModelExprVal(vsc::IModelExprVal *e) override;

	virtual void visitModelExprVecSubscript(vsc::IModelExprVecSubscript *e) override;

#ifdef UNDEFINED

	virtual void visitModelField(vsc::IModelField *f) { }
#endif

	virtual void visitModelFieldRef(vsc::IModelFieldRef *f) override;

	virtual void visitModelFieldRefRoot(vsc::IModelFieldRef *f) override;

	virtual void visitModelFieldRefType(vsc::IModelFieldRef *f) override;

	virtual void visitModelFieldRoot(vsc::IModelFieldRoot *f) override;

	virtual void visitModelFieldType(vsc::IModelFieldType *f) override;

#ifdef UNDEFINED
	virtual void visitModelFieldVec(vsc::IModelFieldVec *f) { }

	virtual void visitModelFieldVecRoot(vsc::IModelFieldVecRoot *f) { }
#endif

	virtual void visitTypeConstraintBlock(vsc::ITypeConstraintBlock *c) override;

	virtual void visitTypeConstraintExpr(vsc::ITypeConstraintExpr *c) override;

	virtual void visitTypeConstraintIfElse(vsc::ITypeConstraintIfElse *c) override;

	virtual void visitTypeConstraintImplies(vsc::ITypeConstraintImplies *c) override;

	virtual void visitTypeConstraintScope(vsc::ITypeConstraintScope *c) override;

	virtual void visitTypeExprBin(vsc::ITypeExprBin *e) override;

	virtual void visitTypeExprFieldRef(vsc::ITypeExprFieldRef *e) override;

	virtual void visitTypeExprRange(vsc::ITypeExprRange *e) override;

	virtual void visitTypeExprRangelist(vsc::ITypeExprRangelist *e) override;

	virtual void visitTypeExprVal(vsc::ITypeExprVal *e) override;

#ifdef UNDEFINED
	virtual void visitTypeField(vsc::ITypeField *f) { }
#endif

private:
	PyObject				*m_obj;

};

