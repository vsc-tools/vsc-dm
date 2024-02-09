/*
 * VisitorDelegator.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IVisitor.h"

namespace vsc {
namespace dm {

class VisitorDelegator : public virtual IVisitor {
public:

	VisitorDelegator(IVisitor *delegate, bool cascade=true) : 
		m_delegate(delegate), m_cascade(cascade) { }

	virtual bool cascade() const override { return m_cascade; }

	virtual void visitDataTypeArray(IDataTypeArray *t) override {
        m_delegate->visitDataTypeArray(t);
    }

	virtual void visitDataTypeBool(IDataTypeBool *t) override {
        m_delegate->visitDataTypeBool(t);
    }

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override {
		m_delegate->visitDataTypeEnum(t);
	}

	virtual void visitDataTypeInt(IDataTypeInt *t) override {
		m_delegate->visitDataTypeInt(t);
	}

	virtual void visitDataTypePtr(IDataTypePtr *t) override {
        m_delegate->visitDataTypePtr(t);
    }

	virtual void visitDataTypeString(IDataTypeString *t) override {
		m_delegate->visitDataTypeString(t);
	}

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {
		m_delegate->visitDataTypeStruct(t);
	}

	virtual void visitDataTypeTypeRef(IDataTypeTypeRef *t) override {
		m_delegate->visitDataTypeTypeRef(t);
	}

    virtual void visitDataTypeWrapper(IDataTypeWrapper *t) override {
        m_delegate->visitDataTypeWrapper(t);
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

	virtual void visitModelConstraintForeach(IModelConstraintForeach *c) override {
		m_delegate->visitModelConstraintForeach(c);
	}

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) override {
		m_delegate->visitModelConstraintIfElse(c);
	}

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override {
		m_delegate->visitModelConstraintImplies(c);
	}

	virtual void visitModelConstraintRef(IModelConstraintRef *c) override {
		m_delegate->visitModelConstraintRef(c);
	}

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override {
		m_delegate->visitModelConstraintScope(c);
	}

	virtual void visitModelConstraintSelect(IModelConstraintSelect *c) override {
		m_delegate->visitModelConstraintSelect(c);
	}

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override {
		m_delegate->visitModelConstraintSoft(c);
	}

	virtual void visitModelConstraintSubst(IModelConstraintSubst *c) override {
		m_delegate->visitModelConstraintSubst(c);
	}

	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) override {
		m_delegate->visitModelConstraintUnique(c);
	}

	virtual void visitModelCoverBinMask(IModelCoverBinMask *c) override {
		m_delegate->visitModelCoverBinMask(c);
	}

	virtual void visitModelCoverBinSingleRange(IModelCoverBinSingleRange *c) override {
		m_delegate->visitModelCoverBinSingleRange(c);
	}

	virtual void visitModelCoverBinSingleVal(IModelCoverBinSingleVal *c) override {
		m_delegate->visitModelCoverBinSingleVal(c);
	}

	virtual void visitModelCoverBinCollection(IModelCoverBinCollection *c) override {
		m_delegate->visitModelCoverBinCollection(c);
	}

	virtual void visitModelCoverCross(IModelCoverCross *c) override {
		m_delegate->visitModelCoverCross(c);
	}

	virtual void visitModelCovergroup(IModelCovergroup *c) override {
		m_delegate->visitModelCovergroup(c);
	}

	virtual void visitModelCoverpoint(IModelCoverpoint *c) override {
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

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override { 
		m_delegate->visitModelExprIndexedFieldRef(e);
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

	virtual void visitModelFieldRefType(IModelFieldTypeRef *f) override {
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

	virtual void visitTypeConstraintIfElse(ITypeConstraintIfElse *c) override {
		m_delegate->visitTypeConstraintIfElse(c);
	}

	virtual void visitTypeConstraintImplies(ITypeConstraintImplies *c) override {
		m_delegate->visitTypeConstraintImplies(c);
	}

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) override {
		m_delegate->visitTypeConstraintScope(c);
	}

	virtual void visitTypeConstraintSoft(ITypeConstraintSoft *c) override {
		m_delegate->visitTypeConstraintSoft(c);
	}

	virtual void visitTypeConstraintUnique(ITypeConstraintUnique *c) override {
		m_delegate->visitTypeConstraintUnique(c);
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

	virtual void visitTypeExprRef(ITypeExprRef *e) override {
        m_delegate->visitTypeExprRef(e);
    }

	virtual void visitTypeExprUnary(ITypeExprUnary *e) override {
        m_delegate->visitTypeExprUnary(e);
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

	virtual void visitTypeFieldVec(ITypeFieldVec *f) override {
		m_delegate->visitTypeFieldVec(f);
	}

protected:
	IVisitor *delegate() const { return m_delegate; }

protected:
	bool					m_cascade;
	IVisitor				*m_delegate;

};

}
}
