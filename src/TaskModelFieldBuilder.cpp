/*
 * TaskModelFieldBuilder.cpp
 *
 *  Created on: Apr 9, 2022
 *      Author: mballance
 */

#include "dmgr/impl/DebugMacros.h"
#include "TaskModelExprBuilder.h"
#include "TaskModelFieldBuilder.h"

#include "vsc/dm/IDataTypeStruct.h"
#include "vsc/dm/IModelFieldRoot.h"
#include "vsc/dm/IModelFieldType.h"

namespace vsc {
namespace dm {

TaskModelFieldBuilder::TaskModelFieldBuilder(IContext *ctxt) :
		m_ctxt(ctxt), m_type_field(0) {
    DEBUG_INIT("TaskModelFieldBuilder", ctxt->getDebugMgr());
}

TaskModelFieldBuilder::~TaskModelFieldBuilder() {
	// TODO Auto-generated destructor stub
}

IModelFieldRoot *TaskModelFieldBuilder::build(
		IDataTypeStruct 		*type,
		const std::string		&name) {
	DEBUG_ENTER("build");
	m_field_s.clear();
	m_constraint_s.clear();
	m_name = name; // TODO:
	m_type_field = 0;
	type->accept(this);
	DEBUG_LEAVE("build");
	fprintf(stdout, "TaskModelFieldBuilder: %p %p\n",
			m_field_s.at(0),
			dynamic_cast<IModelFieldRoot *>(m_field_s.at(0)));
	return dynamic_cast<IModelFieldRoot *>(m_field_s.at(0));
}

void TaskModelFieldBuilder::visitTypeField(ITypeField *f) {
	DEBUG_ENTER("visitTypeField");
	IModelFieldType *field = m_ctxt->mkModelFieldType(f);
	m_field_s.back()->addField(field);

	m_field_s.push_back(field);
	VisitorBase::visitTypeField(f);
	m_field_s.pop_back();
	DEBUG_LEAVE("visitTypeField");
}

void TaskModelFieldBuilder::visitDataTypeInt(IDataTypeInt *t) {

}

void TaskModelFieldBuilder::visitDataTypeStruct(IDataTypeStruct *t) {
	DEBUG_ENTER("visitDataTypeStruct %d %d",
			t->getFields().size(),
			t->getConstraints().size());
	if (m_field_s.size() == 0) {
		IModelFieldRoot *field = m_ctxt->mkModelFieldRoot(t, m_name);

		m_field_s.push_back(field);
	}

	// Visit the members
	VisitorBase::visitDataTypeStruct(t);
	DEBUG_LEAVE("visitDataTypeStruct");
}

void TaskModelFieldBuilder::visitTypeConstraintBlock(ITypeConstraintBlock *c) {
	DEBUG_ENTER("visitTypeConstraintBlock");
	IModelConstraintBlock *cm = m_ctxt->mkModelConstraintBlock(c->name());

	m_constraint_s.push_back(cm);
	for (auto it=c->constraints().begin(); it!=c->constraints().end(); it++) {
		(*it)->accept(this);
	}

	m_constraint_s.pop_back();

	if (m_constraint_s.size() == 0) {
		m_field_s.back()->addConstraint(cm);
	}
	DEBUG_LEAVE("visitTypeConstraintBlock");
}

void TaskModelFieldBuilder::visitTypeConstraintExpr(ITypeConstraintExpr *c) {
	DEBUG_ENTER("visitTypeConstraintExpr");

	// Convert type expression to a model expression
	IModelExpr *expr = TaskModelExprBuilder(
			m_ctxt, m_field_s.back()).build(c->expr());

	IModelConstraintExpr *cm = m_ctxt->mkModelConstraintExpr(expr);

	m_constraint_s.back()->addConstraint(cm);

	DEBUG_LEAVE("visitTypeConstraintExpr");
}

void TaskModelFieldBuilder::visitTypeConstraintScope(ITypeConstraintScope *c) {
	DEBUG_ENTER("visitTypeConstraintScope");
	VisitorBase::visitTypeConstraintScope(c);
	DEBUG_LEAVE("visitTypeConstraintScope");
}

dmgr::IDebug *TaskModelFieldBuilder::m_dbg = 0;

}
} /* namespace vsc */
