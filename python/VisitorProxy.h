/*
 * VisitorProxy.h
 *
 *  Created on: Feb 13, 2022
 *      Author: mballance
 */

#pragma once
#include <Python.h>
#include "vsc/dm/impl/VisitorBase.h"
#include "vsc/dm/IModelExprBin.h"

class VisitorProxy : public vsc::dm::VisitorBase {
public:
	VisitorProxy(PyObject *obj);

	virtual ~VisitorProxy();

	virtual void visitDataTypeEnum(vsc::dm::IDataTypeEnum *t) override;

	virtual void visitDataTypeInt(vsc::dm::IDataTypeInt *t) override;

	virtual void visitDataTypeStruct(vsc::dm::IDataTypeStruct *t) override;

#ifdef UNDEFINED
	virtual void visitModelConstraint(vsc::dm::IModelConstraint *c) { }
#endif

	virtual void visitModelConstraintBlock(vsc::dm::IModelConstraintBlock *c) override;

	virtual void visitModelConstraintExpr(vsc::dm::IModelConstraintExpr *c) override;

	virtual void visitModelConstraintIfElse(vsc::dm::IModelConstraintIfElse *c) override;

	virtual void visitModelConstraintImplies(vsc::dm::IModelConstraintImplies *c) override;

	virtual void visitModelConstraintScope(vsc::dm::IModelConstraintScope *c) override;

#ifdef UNDEFINED

	virtual void visitModelConstraintSoft(vsc::dm::IModelConstraintSoft *c) { }

	virtual void visitModelCoverCross(vsc::dm::ModelCoverCross *c) { }

	virtual void visitModelCovergroup(vsc::dm::ModelCovergroup *c) { }

	virtual void visitModelCoverpoint(vsc::dm::ModelCoverpoint *c) { }
#endif

	virtual void visitModelExprBin(vsc::dm::IModelExprBin *e) override;

	virtual void visitModelExprCond(vsc::dm::IModelExprCond *e) override;

	virtual void visitModelExprFieldRef(vsc::dm::IModelExprFieldRef *e) override;

	virtual void visitModelExprIn(vsc::dm::IModelExprIn *e) override;

	virtual void visitModelExprPartSelect(vsc::dm::IModelExprPartSelect *e) override;

	virtual void visitModelExprRange(vsc::dm::IModelExprRange *e) override;

	virtual void visitModelExprRangelist(vsc::dm::IModelExprRangelist *e) override;

	virtual void visitModelExprRef(vsc::dm::IModelExprRef *e) override;

	virtual void visitModelExprUnary(vsc::dm::IModelExprUnary *e) override;

	virtual void visitModelExprVecSubscript(vsc::dm::IModelExprVecSubscript *e) override;

#ifdef UNDEFINED

	virtual void visitModelField(vsc::dm::IModelField *f) { }
#endif

	virtual void visitModelFieldRef(vsc::dm::IModelFieldRef *f) override;

	virtual void visitModelFieldRefRoot(vsc::dm::IModelFieldRef *f) override;

	virtual void visitModelFieldRefType(vsc::dm::IModelFieldTypeRef *f) override;

	virtual void visitModelFieldRoot(vsc::dm::IModelFieldRoot *f) override;

	virtual void visitModelFieldType(vsc::dm::IModelFieldType *f) override;

#ifdef UNDEFINED
	virtual void visitModelFieldVec(vsc::dm::IModelFieldVec *f) { }

	virtual void visitModelFieldVecRoot(vsc::dm::IModelFieldVecRoot *f) { }
#endif

	virtual void visitTypeConstraintBlock(vsc::dm::ITypeConstraintBlock *c) override;

	virtual void visitTypeConstraintExpr(vsc::dm::ITypeConstraintExpr *c) override;

	virtual void visitTypeConstraintIfElse(vsc::dm::ITypeConstraintIfElse *c) override;

	virtual void visitTypeConstraintImplies(vsc::dm::ITypeConstraintImplies *c) override;

	virtual void visitTypeConstraintScope(vsc::dm::ITypeConstraintScope *c) override;

	virtual void visitTypeExprBin(vsc::dm::ITypeExprBin *e) override;

	virtual void visitTypeExprEnumRef(vsc::dm::ITypeExprEnumRef *e) override;

	virtual void visitTypeExprFieldRef(vsc::dm::ITypeExprFieldRef *e) override;

	virtual void visitTypeExprRange(vsc::dm::ITypeExprRange *e) override;

	virtual void visitTypeExprRangelist(vsc::dm::ITypeExprRangelist *e) override;

	virtual void visitTypeExprVal(vsc::dm::ITypeExprVal *e) override;

#ifdef UNDEFINED
	virtual void visitTypeField(vsc::dm::ITypeField *f) { }
#endif

private:
	PyObject				*m_obj;

};

