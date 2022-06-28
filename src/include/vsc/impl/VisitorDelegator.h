/*
 * VisitorDelegator.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IVisitor.h"

namespace vsc {

class VisitorDelegator : public virtual IVisitor {
public:

	VisitorDelegator(IVisitor *delegate) : m_delegate(delegate) { }

	virtual void visitDataTypeInt(IDataTypeInt *t) override {
		m_delegate->visitDataTypeInt(t);
	}

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {
		m_delegate->visitDataTypeStruct(t);
	}

	virtual void visitModelConstraint(IModelConstraint *c) override {
		m_delegate->visitModelConstraint(c);
	}

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) override {
		m_delegate->visitModelConstraintBlock(c);		;
	}

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override {
		m_delegate->visitModelConstraintExpr(c);
	}

	virtual void visitModelConstraintIf(IModelConstraintIf *c) override {
		m_delegate->visitModelConstraintIf(c);
	}

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override {
		m_delegate->visitModelConstraintImplies(c);
	}

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override {
		m_delegate->visitModelConstraintScope(c);
	}

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override {
		m_delegate->visitModelConstraintSoft(c);
	}

	virtual void visitModelCoverCross(ModelCoverCross *c) override {
		m_delegate->visitModelCoverCross(c);
	}

	virtual void visitModelCovergroup(ModelCovergroup *c) override {
		m_delegate->visitModelCovergroup(c);
	}

	virtual void visitModelCoverpoint(ModelCoverpoint *c) override {
		m_delegate->visitModelCoverpoint(c);
	}

	virtual void visitModelExprBin(IModelExprBin *e) override {
		m_delegate->visitModelExprBin(e);
	}

	virtual void visitModelExprCond(IModelExprCond *e) override {
		m_delegate->visitModelExprCond(e);
	}

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override {
		m_delegate->visitModelExprFieldRef(e);
	}

	virtual void visitModelExprIn(IModelExprIn *e) override {
		m_delegate->visitModelExprIn(e);
	}

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override {
		m_delegate->visitModelExprPartSelect(e);
	}

	virtual void visitModelExprRange(IModelExprRange *e) override {
		m_delegate->visitModelExprRange(e);
	}

	virtual void visitModelExprRangelist(IModelExprRangelist *e) override {
		m_delegate->visitModelExprRangelist(e);
	}

	virtual void visitModelExprRef(IModelExprRef *e) override {
		m_delegate->visitModelExprRef(e);
	}

	virtual void visitModelExprUnary(IModelExprUnary *e) override {
		m_delegate->visitModelExprUnary(e);
	}

	virtual void visitModelExprVal(IModelExprVal *e) override {
		m_delegate->visitModelExprVal(e);
	}

	virtual void visitModelExprVecSubscript(IModelExprVecSubscript *e) override {
		m_delegate->visitModelExprVecSubscript(e);
	}

	virtual void visitModelField(IModelField *f) override {
		m_delegate->visitModelField(f);
	}

	virtual void visitModelFieldRef(IModelFieldRef *f) override {
		m_delegate->visitModelFieldRef(f);
	}

	virtual void visitModelFieldRefRoot(IModelFieldRef *f) override {
		m_delegate->visitModelFieldRefRoot(f);
	}

	virtual void visitModelFieldRefType(IModelFieldRef *f) override {
		m_delegate->visitModelFieldRefType(f);
	}

	virtual void visitModelFieldRoot(IModelFieldRoot *f) override {
		m_delegate->visitModelFieldRoot(f);
	}

	virtual void visitModelFieldType(IModelFieldType *f) override {
		m_delegate->visitModelFieldType(f);
	}

	virtual void visitModelFieldVec(IModelFieldVec *f) override {
		m_delegate->visitModelFieldVec(f);
	}

	virtual void visitModelFieldVecRoot(IModelFieldVecRoot *f) override {
		m_delegate->visitModelFieldVecRoot(f);
	}

	virtual void visitTypeConstraintBlock(ITypeConstraintBlock *c) override {
		m_delegate->visitTypeConstraintBlock(c);
	}

	virtual void visitTypeConstraintExpr(ITypeConstraintExpr *c) override {
		m_delegate->visitTypeConstraintExpr(c);
	}

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) override {
		m_delegate->visitTypeConstraintScope(c);
	}

	virtual void visitTypeExprBin(ITypeExprBin *e) override {
		m_delegate->visitTypeExprBin(e);
	}

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) override {
		m_delegate->visitTypeExprFieldRef(e);
	}

	virtual void visitTypeExprRange(ITypeExprRange *e) override {
		m_delegate->visitTypeExprRange(e);
	}

	virtual void visitTypeExprRangelist(ITypeExprRangelist *e) override {
		m_delegate->visitTypeExprRangelist(e);
	}

	virtual void visitTypeExprVal(ITypeExprVal *e) override {
		m_delegate->visitTypeExprVal(e);
	}

	virtual void visitTypeField(ITypeField *f) override {
		fprintf(stdout, "visitTypeField\n");
		m_delegate->visitTypeField(f);
	}

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override {
		fprintf(stdout, "visitTypeFieldPhy\n");
		m_delegate->visitTypeFieldPhy(f);
	}

	virtual void visitTypeFieldRef(ITypeFieldRef *f) override {
		m_delegate->visitTypeFieldRef(f);
	}

protected:
	IVisitor *delegate() const { return m_delegate; }

protected:

	IVisitor				*m_delegate;

};

}
