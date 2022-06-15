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
#include "vsc/impl/VisitorBase.h"

namespace vsc {
class TaskBuildModelField : public VisitorBase {
public:

	TaskBuildModelField(IModelBuildContext *ctxt, IVisitor *this_p=0) :
		VisitorBase(this_p), m_ctxt(ctxt), m_type_field(0) { }

	virtual ~TaskBuildModelField() { }

	const std::string &name() const { return m_name; }

	virtual IModelField *build(IDataTypeStruct *type, const std::string &name) {
		m_constraint_s.clear();
		m_name = name; // TODO:
		m_type_field = 0;
		type->accept(m_this);

		return m_ctxt->getField(0);
	}

	virtual void visitTypeFieldPhy(ITypeFieldPhy *f) override {
		IModelFieldType *field = m_ctxt->ctxt()->mkModelFieldType(f);
		m_ctxt->getField(-1)->addField(field);
		fprintf(stdout, "visitTypeFieldPhy: %s\n", f->name().c_str());

		if (f->getInit()) {
			field->val()->set(f->getInit());
		}

		m_ctxt->pushField(field);
		VisitorBase::visitTypeField(f);
		m_ctxt->popField();
	}

	virtual void visitDataTypeInt(IDataTypeInt *t) override {
		;
	}

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override {
		if (m_ctxt->fieldStackSize() == 0) {
			IModelFieldRoot *field = m_ctxt->ctxt()->mkModelFieldRoot(t, m_name);

			m_ctxt->pushField(field);
		}

		// Visit the members
		VisitorBase::visitDataTypeStruct(t);
	}

	virtual void visitTypeConstraintBlock(ITypeConstraintBlock *c) override {
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

	virtual void visitTypeConstraintExpr(ITypeConstraintExpr *c) override {
		// Convert type expression to a model expression
		IModelExpr *expr = TaskBuildModelExpr(m_ctxt).build(c->expr());

		IModelConstraintExpr *cm = m_ctxt->ctxt()->mkModelConstraintExpr(expr);

		m_constraint_s.back()->add_constraint(cm);
	}

	virtual void visitTypeConstraintScope(ITypeConstraintScope *c) override {
		VisitorBase::visitTypeConstraintScope(c);
	}

protected:
	IModelBuildContext						*m_ctxt;
	std::string								m_name;
	ITypeField								*m_type_field;
	std::vector<IModelConstraintScope *>	m_constraint_s;
};

}
