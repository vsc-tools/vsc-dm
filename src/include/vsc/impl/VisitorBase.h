/*
 * VisitorBase.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IVisitor.h"

#include "vsc/IDataTypeEnum.h"
#include "vsc/IDataTypeInt.h"
#include "vsc/IDataTypeStruct.h"
#include "vsc/IDataTypeTypeRef.h"

#include "vsc/IModelConstraintBlock.h"
#include "vsc/IModelConstraintExpr.h"
#include "vsc/IModelConstraintForeach.h"
#include "vsc/IModelConstraintIfElse.h"
#include "vsc/IModelConstraintImplies.h"
#include "vsc/IModelConstraintRef.h"
#include "vsc/IModelConstraintScope.h"
#include "vsc/IModelConstraintSelect.h"
#include "vsc/IModelConstraintSoft.h"
#include "vsc/IModelConstraintSubst.h"
#include "vsc/IModelConstraintUnique.h"

#include "vsc/IModelCoverBinCollection.h"
#include "vsc/IModelCoverBinMask.h"
#include "vsc/IModelCoverBinSingleRange.h"
#include "vsc/IModelCoverBinSingleVal.h"
#include "vsc/IModelCoverCross.h"
#include "vsc/IModelCovergroup.h"
#include "vsc/IModelCoverpoint.h"


#include "vsc/IModelExprBin.h"
#include "vsc/IModelExprCond.h"
#include "vsc/IModelExprFieldRef.h"
#include "vsc/IModelExprIn.h"
#include "vsc/IModelExprIndexedFieldRef.h"
#include "vsc/IModelExprPartSelect.h"
#include "vsc/IModelExprRange.h"
#include "vsc/IModelExprRangelist.h"
#include "vsc/IModelExprRef.h"
#include "vsc/IModelExprUnary.h"
#include "vsc/IModelExprVal.h"
#include "vsc/IModelExprVecSubscript.h"

#include "vsc/IModelField.h"
#include "vsc/IModelFieldRef.h"
#include "vsc/IModelFieldRoot.h"
#include "vsc/IModelFieldType.h"
#include "vsc/IModelFieldTypeRef.h"
#include "vsc/IModelFieldVec.h"
#include "vsc/IModelFieldVecRoot.h"

#include "vsc/IModelVal.h"

#include "vsc/ITypeExprBin.h"
#include "vsc/ITypeExprRange.h"
#include "vsc/ITypeExprRangelist.h"

#include "vsc/ITypeConstraintBlock.h"
#include "vsc/ITypeConstraintExpr.h"
#include "vsc/ITypeConstraintIfElse.h"
#include "vsc/ITypeConstraintImplies.h"
#include "vsc/ITypeConstraintScope.h"
#include "vsc/ITypeConstraintSoft.h"
#include "vsc/ITypeConstraintUnique.h"

#include "vsc/ITypeField.h"
#include "vsc/ITypeFieldPhy.h"
#include "vsc/ITypeFieldRef.h"
#include "vsc/ITypeFieldVec.h"


namespace vsc {

class VisitorBase : public virtual IVisitor {
public:

	VisitorBase(bool cascade=true, IVisitor *this_p=0) : 
		m_cascade(cascade), m_this((this_p)?this_p:this) { }

	virtual ~VisitorBase() { }

	virtual bool cascade() const { return m_cascade; }

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override { }

	virtual void visitDataTypeInt(IDataTypeInt *t) override { }

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {
		for (auto it=t->getFields().begin(); it!=t->getFields().end(); it++) {
			(*it)->accept(m_this);
		}
		for (auto it=t->getConstraints().begin();
				it!=t->getConstraints().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitDataTypeTypeRef(IDataTypeTypeRef *t) override {
		// Don't propagate by default
	}

	virtual void visitModelConstraint(IModelConstraint *c) override { }

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) override {
		visitModelConstraintScope(c);		;
	}

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override {
		visitModelConstraint(c);
		c->expr()->accept(m_this);
	}

	virtual void visitModelConstraintForeach(IModelConstraintForeach *c) override {
		c->getTarget()->accept(m_this);
		visitModelConstraintScope(c);
	}

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) override { 
		c->getCond()->accept(m_this);
		c->getTrue()->accept(m_this);
		if (c->getFalse()) {
			c->getFalse()->accept(m_this);
		}
	}

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override { 
		c->getCond()->accept(m_this);
		c->getBody()->accept(m_this);
	}

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override {
		for (std::vector<IModelConstraintUP>::const_iterator
				it=c->constraints().begin();
				it!=c->constraints().end(); it++) {
			it->get()->accept(m_this);
		}
	}

	virtual void visitModelConstraintSelect(IModelConstraintSelect *c) override {
		c->getLhs()->accept(this);

		for (std::vector<IModelField *>::const_iterator
			it=c->getRhs().begin();
			it!=c->getRhs().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitModelConstraintRef(IModelConstraintRef *c) override { 
		c->getTarget()->accept(m_this);
	}

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override { 
		c->constraint()->accept(m_this);
	}

	virtual void visitModelConstraintSubst(IModelConstraintSubst *c) override {
		c->getOriginal()->accept(m_this);
		visitModelConstraintScope(c);
	}

	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) override { 
		for (std::vector<IModelExprUP>::const_iterator
			it=c->getExprs().begin();
			it!=c->getExprs().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitModelCoverBinMask(IModelCoverBinMask *c) override { }

	virtual void visitModelCoverBinCollection(IModelCoverBinCollection *c) override { }

	virtual void visitModelCoverBinSingleRange(IModelCoverBinSingleRange *c) override { }

	virtual void visitModelCoverBinSingleVal(IModelCoverBinSingleVal *c) override { }

	virtual void visitModelCoverCross(IModelCoverCross *c) override { }

	virtual void visitModelCovergroup(IModelCovergroup *c) override { }

	virtual void visitModelCoverpoint(IModelCoverpoint *c) override { }

	virtual void visitModelExprBin(IModelExprBin *e) override {
		e->lhs()->accept(m_this);
		e->rhs()->accept(m_this);
	}

	virtual void visitModelExprCond(IModelExprCond *e) override {
		e->getCond()->accept(m_this);
		e->getTrue()->accept(m_this);
		e->getFalse()->accept(m_this);
	}

	virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override { }

	virtual void visitModelExprIn(IModelExprIn *e) override {
		e->lhs()->accept(m_this);
		e->rangelist()->accept(m_this);
	}

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override { }

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override { }

	virtual void visitModelExprRange(IModelExprRange *e) override { }

	virtual void visitModelExprRangelist(IModelExprRangelist *e) override { }

	virtual void visitModelExprRef(IModelExprRef *e) override {
		e->expr()->accept(m_this);
	}

	virtual void visitModelExprUnary(IModelExprUnary *e) override {
		e->expr()->accept(m_this);
	}

	virtual void visitModelExprVal(IModelExprVal *e) override { }

	virtual void visitModelExprVecSubscript(IModelExprVecSubscript *e) override {
		e->expr()->accept(m_this);
		e->subscript()->accept(m_this);
	}

	virtual void visitModelField(IModelField *f) override {
		if (f->getDataType()) {
			f->getDataType()->accept(m_this);
		}
		for (auto it=f->fields().begin();
				it!=f->fields().end(); it++) {
			(*it)->accept(m_this);
		}
		for (auto it=f->constraints().begin();
				it!=f->constraints().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitModelFieldRef(IModelFieldRef *f) override {
		if (f->getRef()) {
			visitModelField(f);
		}
	}

	virtual void visitModelFieldRefRoot(IModelFieldRef *f) override {
		visitModelFieldRef(f);
	}

	virtual void visitModelFieldRefType(IModelFieldTypeRef *f) override {
		visitModelFieldRef(f);
	}

	virtual void visitModelFieldRoot(IModelFieldRoot *f) override {
		visitModelField(f);
	}

	virtual void visitModelFieldType(IModelFieldType *f) override {
		visitModelField(f);
	}

	virtual void visitModelFieldVec(IModelFieldVec *f) override {
		f->getSizeRef()->accept(m_this);
		visitModelField(f);
	}

	virtual void visitModelFieldVecRoot(IModelFieldVecRoot *f) override {
		visitModelFieldVec(f);
	}

	virtual void visitTypeConstraintBlock(ITypeConstraintBlock *c) override {
		visitTypeConstraintScope(c);
	}
	
	virtual void visitTypeConstraintExpr(ITypeConstraintExpr *c) override {
		c->expr()->accept(m_this);
	}

	virtual void visitTypeConstraintIfElse(ITypeConstraintIfElse *c) override {
		c->getCond()->accept(m_this);
		c->getTrue()->accept(m_this);
		if (c->getFalse()) {
			c->getFalse()->accept(m_this);
		}
	}

	virtual void visitTypeConstraintImplies(ITypeConstraintImplies *c) override {
		c->getCond()->accept(m_this);
		c->getBody()->accept(m_this);
	}

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) override {
		for (auto it=c->constraints().begin(); it!=c->constraints().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitTypeConstraintSoft(ITypeConstraintSoft *c) override {
		c->constraint()->accept(m_this);
	}

	virtual void visitTypeConstraintUnique(ITypeConstraintUnique *c) override {
		for (std::vector<ITypeExprUP>::const_iterator
			it=c->getExprs().begin();
			it!=c->getExprs().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitTypeExprBin(ITypeExprBin *e) override {
		e->lhs()->accept(m_this);
		e->rhs()->accept(m_this);
	}

	virtual void visitTypeExprFieldRef(ITypeExprFieldRef *e) override { }

	virtual void visitTypeExprRange(ITypeExprRange *e) override {
		if (e->lower()) {
			e->lower()->accept(m_this);
		}
		if (e->upper()) {
			e->upper()->accept(m_this);
		}
	}

	virtual void visitTypeExprRangelist(ITypeExprRangelist *e) override {
		for (std::vector<ITypeExprRangeUP>::const_iterator
				it=e->getRanges().begin();
				it!=e->getRanges().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitTypeExprVal(ITypeExprVal *e) override { }

	virtual void visitTypeField(ITypeField *f) override {
		if (f->getDataType()) {
			f->getDataType()->accept(m_this);
		}
	}

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override {
		m_this->visitTypeField(f);
	}

	virtual void visitTypeFieldRef(ITypeFieldRef *f) override {
		if (f->getDataType()) {
			f->getDataType()->accept(m_this);
		}
	}

	virtual void visitTypeFieldVec(ITypeFieldVec *f) override {
		if (f->getDataType()) {
			f->getDataType()->accept(m_this);
		}
	}

protected:
	bool						m_cascade;
	IVisitor					*m_this;
};

}
