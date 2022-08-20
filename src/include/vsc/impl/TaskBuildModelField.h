/*
 * TaskBuildModelField.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 */

#pragma once
#include <string>
#include <vector>
#include "vsc/IContext.h"
#include "vsc/IModelBuildContext.h"
#include "vsc/impl/TaskBuildModelExpr.h"
#include "vsc/impl/TaskEvalTypeExpr.h"
#include "vsc/impl/VisitorBase.h"
#include "TaskBuildModelExpr.h"

namespace vsc {
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

		IModelField *ret = m_ctxt->getField(0);
		m_ctxt->popField();

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

		IModelField *ret = m_ctxt->getField(0);
		m_ctxt->popField();

		return ret;
	}

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override {
		if (m_pass == 0) {
			IModelFieldType *field = m_ctxt->ctxt()->mkModelFieldType(f);

			addField(field);

			fprintf(stdout, "visitTypeFieldPhy: %s\n", f->name().c_str());

			if (f->getInit()) {
				field->val()->set(f->getInit());
			}

			m_ctxt->pushField(field);
			VisitorBase::visitTypeField(f);
			m_ctxt->popField();
		} else if (m_pass == 1) {
			// The level above will have populated the field
			VisitorBase::visitTypeField(f);
		}
	}

	virtual void visitTypeFieldRef(ITypeFieldRef *f) override {
		fprintf(stdout, "visitTypeFieldRef: %s\n", f->name().c_str());
		IModelFieldRef *field = m_ctxt->ctxt()->mkModelFieldRefType(f);
		addField(field);
	}

	virtual void visitDataTypeEnum(IDataTypeEnum *t) override {
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
								)));

		addField(field);
	}

	virtual void visitDataTypeInt(IDataTypeInt *t) override {
		IModelFieldRoot *field = m_ctxt->ctxt()->mkModelFieldRoot(
				t,
				m_name);
		addField(field);
	}

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {

		if (m_pass == 0) {
			if (m_ctxt->fieldStackSize() == 0) {
				IModelFieldRoot *field = m_ctxt->ctxt()->mkModelFieldRoot(t, m_name);
				m_ctxt->pushField(field);
			}

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
			for (auto it=c->constraints().begin(); it!=c->constraints().end(); it++) {
				(*it)->accept(m_this);
			}

			m_constraint_s.pop_back();

			if (m_constraint_s.size() == 0) {
				m_ctxt->getField(-1)->addConstraint(cm);
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
				m_constraint_s.back()->addConstraint(cm);
			} else {
				m_ctxt->getField(-1)->addConstraint(cm);
			}
		}
	}

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) override {
		VisitorBase::visitTypeConstraintScope(c);
	}

protected:
	void addField(IModelField *f) {
		fprintf(stdout, "addField: %s %d\n", f->name().c_str(), m_ctxt->fieldStackSize());
		if (m_ctxt->fieldStackSize() == 0) {
			m_ctxt->pushField(f);
		} else {
			m_ctxt->getField(-1)->addField(f);
		}
	}

protected:
	uint32_t								m_pass;
	IModelBuildContext						*m_ctxt;
	std::string								m_name;
	ITypeField								*m_type_field;
	std::vector<IModelConstraintScope *>	m_constraint_s;
};

}
