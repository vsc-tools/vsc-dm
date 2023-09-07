/*
 * TaskBuildModelField.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 * 
 * Copyright 2019-2023 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#pragma once
#include <string>
#include <vector>
#include "vsc/dm/IContext.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/impl/TaskBuildModelExpr.h"
#include "vsc/dm/impl/TaskEvalTypeExpr.h"
#include "vsc/dm/impl/VisitorBase.h"
#include "TaskBuildModelExpr.h"

namespace vsc {
namespace dm {

class TaskBuildModelField : public virtual VisitorBase {
public:

	TaskBuildModelField(IVisitor *this_p=0) : 
		VisitorBase(this_p), m_ctxt(0), m_type_field(0) { };

	TaskBuildModelField(IModelBuildContext *ctxt, IVisitor *this_p=0) :
		VisitorBase(this_p), m_ctxt(ctxt), m_type_field(0) { 
		m_pass = 0;
	}

	virtual ~TaskBuildModelField() { }

	const std::string &name() const { return m_name; }

	virtual IModelField *build(IDataType *type, const std::string &name) {
		m_constraint_s.clear();
		m_name = name; // TODO:
		m_type_field = 0;

		m_pass = 0; // First, build out all fields
		type->accept(m_this);

		m_pass = 1; // Now, build out constraints
		type->accept(m_this);

		IModelField *ret = m_ctxt->getTopDownScope();
		m_ctxt->popTopDownScope();

		return ret;
	}

	virtual IModelField *build(ITypeField *type) {
		m_constraint_s.clear();
		m_name = type->name(); // TODO:
		m_type_field = 0;

		m_pass = 0; // First, build out all fields
		type->accept(m_this);

		m_pass = 1; // Now, build out constraints
		type->accept(m_this);

		IModelField *ret = m_ctxt->getTopDownScope();
		m_ctxt->popTopDownScope();

		return ret;
	}

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override {
#ifdef UNDEFINED
		if (m_pass == 0) {
			IModelFieldType *field = m_ctxt->ctxt()->mkModelFieldType(f);

			addField(field);

			fprintf(stdout, "visitTypeFieldPhy: %s\n", f->name().c_str());

            fprintf(stdout, "TODO: Handle initial value\n");
            /*
			if (f->getInit()) {
				field->val()->set(f->getInit());
			}
             */

			m_ctxt->pushTopDownScope(field);
			VisitorBase::visitTypeField(f);
			m_ctxt->popTopDownScope();
		} else if (m_pass == 1) {
			// The level above will have populated the field
			VisitorBase::visitTypeField(f);
		}
#endif
	}

	virtual void visitTypeFieldRef(ITypeFieldRef *f) override {
		fprintf(stdout, "visitTypeFieldRef: %s\n", f->name().c_str());
		IModelFieldRef *field = m_ctxt->ctxt()->mkModelFieldRefType(f);
		addField(field);
	}

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override {
#ifdef UNDEFINED
		ITypeExprRangelist *domain = t->getDomain();
		IModelFieldRoot *field = m_ctxt->ctxt()->mkModelFieldRoot(
				t,
				m_name);

		TaskEvalTypeExpr().eval(
				field->val(),
				domain->getRanges().at(0).get()->lower());

		// Build a constraint for the domain
		field->addConstraint(
				m_ctxt->ctxt()->mkModelConstraintExpr(
						m_ctxt->ctxt()->mkModelExprIn(
								m_ctxt->ctxt()->mkModelExprFieldRef(field),
								TaskBuildModelExpr(m_ctxt).buildT<IModelExprRangelist>(domain)
								)), true);

		addField(field);
#endif /* UNDEFINED */
	}

	virtual void visitDataTypeInt(IDataTypeInt *t) override {
/*
		IModelFieldRoot *field = m_ctxt->ctxt()->mkModelFieldRoot(
				t,
				m_name);
		addField(field);
 */
	}

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {

		if (m_pass == 0) {
#ifdef UNDEFINED
			if (m_ctxt->fieldStackSize() == 0) {
				IModelFieldRoot *field = m_ctxt->ctxt()->mkModelFieldRoot(t, m_name);
				m_ctxt->pushField(field);
			}
#endif

			for (std::vector<ITypeFieldUP>::const_iterator
				it=t->getFields().begin();
				it!=t->getFields().end(); it++) {
				(*it)->accept(m_this);
			}
		} else if (m_pass == 1) {
			// Pass 1 builds out constraints, since fields are completely built
			for (std::vector<ITypeConstraintUP>::const_iterator
				it=t->getConstraints().begin();
				it!=t->getConstraints().end(); it++) {
				(*it)->accept(m_this);
			}
		}
	}

	virtual void visitTypeConstraintBlock(ITypeConstraintBlock *c) override {
		if (m_pass == 0) {
			// Nothing to do
		} else if (m_pass == 1) {
			IModelConstraintBlock *cm = m_ctxt->ctxt()->mkModelConstraintBlock(c->name());

			m_constraint_s.push_back(cm);
			for (std::vector<ITypeConstraintUP>::const_iterator
                it=c->getConstraints().begin(); 
                it!=c->getConstraints().end(); it++) {
				(*it)->accept(m_this);
			}

			m_constraint_s.pop_back();

			if (m_constraint_s.size() == 0) {
				m_ctxt->getTopDownScope()->addConstraint(cm, true);
			}
		}
	}

	virtual void visitTypeConstraintExpr(ITypeConstraintExpr *c) override {
		if (m_pass == 0) {
		} else if (m_pass == 1) {
			// Convert type expression to a model expression
			IModelExpr *expr = TaskBuildModelExpr(m_ctxt).build(c->expr());

			IModelConstraintExpr *cm = m_ctxt->ctxt()->mkModelConstraintExpr(expr);

			if (m_constraint_s.size()) {
				m_constraint_s.back()->addConstraint(cm, true);
			} else {
				m_ctxt->getTopDownScope()->addConstraint(cm, true);
			}
		}
	}

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) override {
		VisitorBase::visitTypeConstraintScope(c);
	}

protected:
	void addField(IModelField *f) {
#ifdef UNDEFINED
		fprintf(stdout, "addField: %s %d\n", f->name().c_str(), m_ctxt->fieldStackSize());
		if (m_ctxt->fieldStackSize() == 0) {
			m_ctxt->pushField(f);
		} else {
			m_ctxt->getField(-1)->addField(f);
		}
#endif
	}

protected:
	uint32_t								m_pass;
	IModelBuildContext						*m_ctxt;
	std::string								m_name;
	ITypeField								*m_type_field;
	std::vector<IModelConstraintScope *>	m_constraint_s;
};

}
}
