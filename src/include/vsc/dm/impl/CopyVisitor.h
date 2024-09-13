/**
 * CopyVisitor.h
 *
 * Copyright 2022 Matthew Ballance and Contributors
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
 * Created on:
 *     Author: 
 */
#pragma once
#include <unordered_map>
#include "dmgr/IDebugMgr.h"
#include "dmgr/impl/DebugMacros.h"
#include "vsc/dm/IContext.h"
#include "vsc/dm/impl/ModelBuildContext.h"
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {



class CopyVisitor : public virtual VisitorBase {
public:
    CopyVisitor(
		IContext 				*ctxt,
		IModelBuildContext		*build_ctxt=0,
		IVisitor 				*this_p=0) : 
		VisitorBase(true, this_p), m_dbg(0), m_ctxt(ctxt),
		m_build_ctxt(build_ctxt?build_ctxt:&m_build_ctxt_l), m_build_ctxt_l(ctxt) {
		DEBUG_INIT("CopyVisitor", ctxt->getDebugMgr());
	}

    virtual ~CopyVisitor() { }

    IAccept *copy(IAccept *src) {
        m_ret = 0;
        src->accept(m_this);
        return m_ret;
    }

	template <class T> T *copyT(IAccept *src) {
		return dynamic_cast<T *>(copy(src));
	}

	virtual void visitModelConstraint(IModelConstraint *c) override { }

	virtual void visitModelConstraintBlock(IModelConstraintBlock *c) override { }

	virtual void visitModelConstraintExpr(IModelConstraintExpr *c) override { 
		DEBUG_ENTER("visitModelConstraintExpr");
		IModelExpr *expr_c = copyT<IModelExpr>(c->expr());

		IModelConstraintExpr *cc = m_ctxt->mkModelConstraintExpr(expr_c);

		ret(cc);

		DEBUG_LEAVE("visitModelConstraintExpr");
	}

	virtual void visitModelConstraintForeach(IModelConstraintForeach *c) override { }

	virtual void visitModelConstraintIfElse(IModelConstraintIfElse *c) override { 
		DEBUG_ENTER("visitModelConstraintIfElse");
		IModelExpr *cond_c = copyT<IModelExpr>(c->getCond());
		IModelConstraint *true_c = copyT<IModelConstraint>(c->getTrue());
		IModelConstraint *false_c = (c->getFalse())?copyT<IModelConstraint>(c->getFalse()):0;

		IModelConstraintIfElse *cc = m_ctxt->mkModelConstraintIfElse(cond_c, true_c, false_c);

		ret(cc);

		DEBUG_LEAVE("visitModelConstraintIfElse");
	}

	virtual void visitModelConstraintImplies(IModelConstraintImplies *c) override { 
		DEBUG_ENTER("visitModelConstraintImplies");

		IModelExpr *cond_c = copyT<IModelExpr>(c->getCond());
		IModelConstraint *body_c = copyT<IModelConstraint>(c->getBody());
		IModelConstraintImplies *cc = m_ctxt->mkModelConstraintImplies(cond_c, body_c);

		ret(cc);

		DEBUG_LEAVE("visitModelConstraintImplies");
	}

	virtual void visitModelConstraintRef(IModelConstraintRef *c) override { }

	virtual void visitModelConstraintScope(IModelConstraintScope *c) override { }

	virtual void visitModelConstraintSelect(IModelConstraintSelect *c) override { }

	virtual void visitModelConstraintSoft(IModelConstraintSoft *c) override { }

	virtual void visitModelConstraintSubst(IModelConstraintSubst *c) override { }

	virtual void visitModelConstraintUnique(IModelConstraintUnique *c) override { }

	virtual void visitModelCoverBinCollection(IModelCoverBinCollection *c) override { }

	virtual void visitModelCoverBinMask(IModelCoverBinMask *c) override { }

	virtual void visitModelCoverBinSingleRange(IModelCoverBinSingleRange *c) override { }

	virtual void visitModelCoverBinSingleVal(IModelCoverBinSingleVal *c) override { }

	virtual void visitModelCoverCross(IModelCoverCross *c) override { }

	virtual void visitModelCovergroup(IModelCovergroup *c) override { }

	virtual void visitModelCoverpoint(IModelCoverpoint *c) override { }

	virtual void visitModelExprBin(IModelExprBin *e) override { 
		DEBUG_ENTER("visitModelExprBin");
		IModelExpr *lhs_c = copyT<IModelExpr>(e->lhs());
		IModelExpr *rhs_c = copyT<IModelExpr>(e->rhs());

		IModelExpr *ec = m_ctxt->mkModelExprBin(
			lhs_c,
			e->op(),
			rhs_c);

		ret(ec);

		DEBUG_LEAVE("visitModelExprBin");
	}

    virtual void visitModelExprCond(IModelExprCond *e) override { 
		DEBUG_ENTER("visitModelExprCond");
		IModelExpr *cond_c = copyT<IModelExpr>(e->getCond());
		IModelExpr *true_c = copyT<IModelExpr>(e->getTrue());
		IModelExpr *false_c = copyT<IModelExpr>(e->getFalse());

		IModelExpr *ec = m_ctxt->mkModelExprCond(cond_c, true_c, false_c);
		
		ret(ec);

		DEBUG_LEAVE("visitModelExprCond");
	}

    virtual void visitModelExprFieldRef(IModelExprFieldRef *e) override { 
		DEBUG_ENTER("visitModelExprFieldRef");
		std::unordered_map<IAccept*,IModelValUP>::const_iterator v_it;
		std::unordered_map<IAccept*,IAccept*>::const_iterator f_it;

		IModelExpr *ec = 0;

		// Two special cases here:
		// - We might be referencing an already-cloned field
		// - We might be referencing a field whose value we should capture instead
		if ((v_it=m_field_val_m.find(e->field())) != m_field_val_m.end()) {
			// Produce a value expression instead
			ec = m_ctxt->mkModelExprVal(v_it->second.get());
		} else if ((f_it=m_obj_m.find(e->field())) != m_obj_m.end()) {
			// Reference the cloned field
			ec = m_ctxt->mkModelExprFieldRef(
				dynamic_cast<IModelField *>(f_it->second));
		} else {
			// Reproduce the reference expression as-is
			ec = m_ctxt->mkModelExprFieldRef(e->field());
		}

		ret(ec);

		DEBUG_LEAVE("visitModelExprFieldRef");
	}

	virtual void visitModelExprIn(IModelExprIn *e) override { }

	virtual void visitModelExprIndexedFieldRef(IModelExprIndexedFieldRef *e) override { 
		DEBUG_ENTER("visitModelExprIndexedFieldRef");

		DEBUG_LEAVE("visitModelExprIndexedFieldRef");
	}

	virtual void visitModelExprPartSelect(IModelExprPartSelect *e) override { }

	virtual void visitModelExprRange(IModelExprRange *e) override { }

	virtual void visitModelExprRangelist(IModelExprRangelist *e) override { }

	virtual void visitModelExprRef(IModelExprRef *e) override { }

	virtual void visitModelExprUnary(IModelExprUnary *e) override { 
		DEBUG_ENTER("visitModelExprUnary");
		IModelExpr *expr_c = copyT<IModelExpr>(e->expr());
		IModelExpr *ec = m_ctxt->mkModelExprUnary(e->op(), expr_c);

		ret(ec);

		DEBUG_LEAVE("visitModelExprUnary");
	}

	virtual void visitModelExprVal(IModelExprVal *e) override { 
		DEBUG_ENTER("visitModelExprVal");

//		IModelExprVal *ec = m_ctxt->mkModelExprVal(e->getVal());
		
//		ret(ec);

		DEBUG_LEAVE("visitModelExprVal");
	}

	virtual void visitModelExprVecSubscript(IModelExprVecSubscript *e) override { }

	virtual void visitModelField(IModelField *f) override { 
		DEBUG_ENTER("visitModelField %s", f->name().c_str());
#ifdef UNDEFINED
		IModelField *fc = m_ctxt->mkModelFieldRoot(f->getDataType(), f->name());

		add_copy(f, fc);

		for (std::vector<IModelFieldUP>::const_iterator
			it=f->getFields().begin();
			it!=f->getFields().end(); it++) {
			fc->addField(copyT<IModelField>(it->get()));
		}

		for (std::vector<IModelConstraintUP>::const_iterator
			it=f->getConstraints().begin();
			it!=f->getConstraints().end(); it++) {
			fc->addConstraint(copyT<IModelConstraint>(it->get()));
		}

		ret(fc);
#endif /* UNDEFINED */

		DEBUG_LEAVE("visitModelField %s", f->name().c_str());
	}

	virtual void visitModelFieldRef(IModelFieldRef *f) override { }

	virtual void visitModelFieldRefRoot(IModelFieldRef *f) override { 

	}

	virtual void visitModelFieldRefType(IModelFieldTypeRef *f) override { 
		DEBUG_ENTER("visitModelFieldRefType %s", f->name().c_str());
		vsc::dm::IModelField *fc = m_ctxt->mkModelFieldRefType(f->getTypeField());

		add_copy(f, fc);

		ret(fc);

		DEBUG_LEAVE("visitModelFieldRefType %s", f->name().c_str());
	}

	virtual void visitModelFieldRoot(IModelFieldRoot *f) override { 

	}

	virtual void visitModelFieldType(IModelFieldType *f) override { 
		DEBUG_ENTER("visitModelFieldType %s", f->name().c_str());
#ifdef UNDEFINED
		vsc::dm::IModelField *fc = m_ctxt->mkModelFieldType(f->getTypeField());

		add_copy(f, fc);

		// TODO: build out sub-fields, constraints, etc

		ret(fc);
#endif /* UNDEFINED */
		DEBUG_LEAVE("visitModelFieldType %s", f->name().c_str());
	}

	virtual void visitModelFieldVec(IModelFieldVec *f) override { }

	virtual void visitModelFieldVecRoot(IModelFieldVecRoot *f) override { }

public:
	void ret(vsc::dm::IAccept *ret) { m_ret = ret; }

	vsc::dm::IAccept *get_copy(vsc::dm::IAccept *s, vsc::dm::IAccept *dflt=0) {
		std::unordered_map<vsc::dm::IAccept*,vsc::dm::IAccept*>::const_iterator it;
		it = m_obj_m.find(s);

		if (it != m_obj_m.end()) {
			return it->second;
		} else {
			return dflt;
		}
	}

	template <class T> T *get_copyT(vsc::dm::IAccept *s, vsc::dm::IAccept *dflt=0) {
		return dynamic_cast<T *>(get_copy(s, dflt));
	}

	void add_copy(vsc::dm::IAccept *s, vsc::dm::IAccept *c) {
		if (m_obj_m.find(s) == m_obj_m.end()) {
			m_obj_m.insert({s, c});
		}
	}

	void set_field_val(vsc::dm::IAccept *f, const vsc::dm::IModelVal *val) {
		std::unordered_map<IAccept *,IModelValUP>::const_iterator it;

		if ((it=m_field_val_m.find(f)) != m_field_val_m.end()) {
			// Update the value
			it->second->set(val);
		} else {
			// Add a new value
			m_field_val_m.insert({f, IModelValUP(val->clone())});
		}
	}

protected:
	dmgr::IDebug									    *m_dbg;
    IContext                    						*m_ctxt;
	IModelBuildContext									*m_build_ctxt;
	ModelBuildContext									m_build_ctxt_l;
    IAccept                     						*m_ret;
	std::unordered_map<vsc::dm::IAccept *,vsc::dm::IAccept *>	m_obj_m;

	// Holds a map of field references that must be converted 
	// to a value
	std::unordered_map<vsc::dm::IAccept *,vsc::dm::IModelValUP>	m_field_val_m;
};


}
}


