/*
 * VisitorBase.h
 *
 * Copyright 2023 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IVisitor.h"

#include "vsc/dm/IDataTypeArray.h"
#include "vsc/dm/IDataTypeBool.h"
#include "vsc/dm/IDataTypeEnum.h"
#include "vsc/dm/IDataTypeInt.h"
#include "vsc/dm/IDataTypeList.h"
#include "vsc/dm/IDataTypePtr.h"
#include "vsc/dm/IDataTypeString.h"
#include "vsc/dm/IDataTypeStruct.h"
#include "vsc/dm/IDataTypeTypeRef.h"
#include "vsc/dm/IDataTypeWrapper.h"

#include "vsc/dm/IModelConstraintBlock.h"
#include "vsc/dm/IModelConstraintExpr.h"
#include "vsc/dm/IModelConstraintForeach.h"
#include "vsc/dm/IModelConstraintIfElse.h"
#include "vsc/dm/IModelConstraintImplies.h"
#include "vsc/dm/IModelConstraintRef.h"
#include "vsc/dm/IModelConstraintScope.h"
#include "vsc/dm/IModelConstraintSelect.h"
#include "vsc/dm/IModelConstraintSoft.h"
#include "vsc/dm/IModelConstraintSubst.h"
#include "vsc/dm/IModelConstraintUnique.h"

#include "vsc/dm/IModelCoverBinCollection.h"
#include "vsc/dm/IModelCoverBinMask.h"
#include "vsc/dm/IModelCoverBinSingleRange.h"
#include "vsc/dm/IModelCoverBinSingleVal.h"
#include "vsc/dm/IModelCoverCross.h"
#include "vsc/dm/IModelCovergroup.h"
#include "vsc/dm/IModelCoverpoint.h"


#include "vsc/dm/IModelExprBin.h"
#include "vsc/dm/IModelExprCond.h"
#include "vsc/dm/IModelExprFieldRef.h"
#include "vsc/dm/IModelExprIn.h"
#include "vsc/dm/IModelExprIndexedFieldRef.h"
#include "vsc/dm/IModelExprPartSelect.h"
#include "vsc/dm/IModelExprRange.h"
#include "vsc/dm/IModelExprRangelist.h"
#include "vsc/dm/IModelExprRef.h"
#include "vsc/dm/IModelExprUnary.h"
#include "vsc/dm/IModelExprVal.h"
#include "vsc/dm/IModelExprVecSubscript.h"

#include "vsc/dm/IModelField.h"
#include "vsc/dm/IModelFieldRef.h"
#include "vsc/dm/IModelFieldRoot.h"
#include "vsc/dm/IModelFieldType.h"
#include "vsc/dm/IModelFieldTypeRef.h"
#include "vsc/dm/IModelFieldVec.h"
#include "vsc/dm/IModelFieldVecRoot.h"

#include "vsc/dm/IModelVal.h"

#include "vsc/dm/ITypeExprArrayLiteral.h"
#include "vsc/dm/ITypeExprArrIndex.h"
#include "vsc/dm/ITypeExprEnumRef.h"
#include "vsc/dm/ITypeExprBin.h"
#include "vsc/dm/ITypeExprRange.h"
#include "vsc/dm/ITypeExprRangelist.h"
#include "vsc/dm/ITypeExprRef.h"
#include "vsc/dm/ITypeExprRefInline.h"
#include "vsc/dm/ITypeExprRefBottomUp.h"
#include "vsc/dm/ITypeExprRefPath.h"
#include "vsc/dm/ITypeExprRefTopDown.h"
#include "vsc/dm/ITypeExprStructLiteral.h"
#include "vsc/dm/ITypeExprSubField.h"
#include "vsc/dm/ITypeExprUnary.h"

#include "vsc/dm/ITypeConstraintBlock.h"
#include "vsc/dm/ITypeConstraintExpr.h"
#include "vsc/dm/ITypeConstraintForeach.h"
#include "vsc/dm/ITypeConstraintIfElse.h"
#include "vsc/dm/ITypeConstraintImplies.h"
#include "vsc/dm/ITypeConstraintScope.h"
#include "vsc/dm/ITypeConstraintSoft.h"
#include "vsc/dm/ITypeConstraintUnique.h"

#include "vsc/dm/ITypeField.h"
#include "vsc/dm/ITypeFieldPhy.h"
#include "vsc/dm/ITypeFieldRef.h"
#include "vsc/dm/ITypeFieldVec.h"


namespace vsc {
namespace dm {

class VisitorBase : public virtual IVisitor {
public:

	VisitorBase(bool cascade=true, IVisitor *this_p=0) : 
		m_cascade(cascade), m_this((this_p)?this_p:this) { }

	virtual ~VisitorBase() { }

	virtual bool cascade() const { return m_cascade; }

	virtual void visitDataTypeArray(IDataTypeArray *t) override { }

	virtual void visitDataTypeBool(IDataTypeBool *t) override { }

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override { }

	virtual void visitDataTypeInt(IDataTypeInt *t) override { }

	virtual void visitDataTypeList(IDataTypeList *t) override { }

	virtual void visitDataTypePtr(IDataTypePtr *t) override { }

	virtual void visitDataTypeString(IDataTypeString *t) override { }

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

    virtual void visitDataTypeWrapper(IDataTypeWrapper *t) override {
        t->getDataTypePhy()->accept(m_this);
        t->getDataTypeVirt()->accept(m_this);
    }

	virtual void visitModelConstraint(IModelConstraint *c) override { }

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) override {
		m_this->visitModelConstraintScope(c);
	}

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override {
		m_this->visitModelConstraint(c);
		c->expr()->accept(m_this);
	}

	virtual void visitModelConstraintForeach(IModelConstraintForeach *c) override {
		c->getTarget()->accept(m_this);
		m_this->visitModelConstraintScope(c);
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
				it=c->getConstraints().begin();
				it!=c->getConstraints().end(); it++) {
			(*it)->accept(m_this);
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
		for (std::vector<IModelFieldUP>::const_iterator 
                it=f->getFields().begin();
				it!=f->getFields().end(); it++) {
			(*it)->accept(m_this);
		}
		for (std::vector<IModelConstraintUP>::const_iterator
                it=f->getConstraints().begin();
				it!=f->getConstraints().end(); it++) {
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

	virtual void visitTypeConstraintForeach(ITypeConstraintForeach *c) override {
        for (std::vector<ITypeVarUP>::const_iterator
            it=c->getVariables().begin();
            it!=c->getVariables().end(); it++) {
            (*it)->accept(m_this);
        }
        c->getBody()->accept(m_this);
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
		for (std::vector<ITypeConstraintUP>::const_iterator
            it=c->getConstraints().begin(); 
            it!=c->getConstraints().end(); it++) {
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

	virtual void visitTypeExprArrayLiteral(ITypeExprArrayLiteral *e) override {
        e->getDataType()->accept(m_this);
    }

	virtual void visitTypeExprArrIndex(ITypeExprArrIndex *e) override {
        e->getRootExpr()->accept(m_this);
        e->getIndexExpr()->accept(m_this);
    }

	virtual void visitTypeExprBin(ITypeExprBin *e) override {
		e->lhs()->accept(m_this);
		e->rhs()->accept(m_this);
	}

    virtual void visitTypeExprEnumRef(ITypeExprEnumRef *e) override { }

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

	virtual void visitTypeExprRef(ITypeExprRef *e) override {
        e->getTarget()->accept(m_this);
    }

	virtual void visitTypeExprRefInline(ITypeExprRefInline *e) override { }
    
	virtual void visitTypeExprRefBottomUp(ITypeExprRefBottomUp *e) override { }

	virtual void visitTypeExprRefPath(ITypeExprRefPath *e) override { }

	virtual void visitTypeExprRefTopDown(ITypeExprRefTopDown *e) override { }
    
    virtual void visitTypeExprStructLiteral(ITypeExprStructLiteral *e) override {
        e->getDataType()->accept(m_this);
    }

	virtual void visitTypeExprSubField(ITypeExprSubField *e) override {
        e->getRootExpr()->accept(m_this);
    }

	virtual void visitTypeExprUnary(ITypeExprUnary *e) override { 
        e->target()->accept(m_this);
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
}
