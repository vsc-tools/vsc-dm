/*
 * TaskModelFieldBuilder.cpp
 *
 *  Created on: Apr 9, 2022
 *      Author: mballance
 */

#include "TaskModelFieldBuilder.h"

namespace vsc {

TaskModelFieldBuilder::TaskModelFieldBuilder(IContext *ctxt) :
		m_ctxt(ctxt), m_type_field(0) {
	// TODO Auto-generated constructor stub

}

TaskModelFieldBuilder::~TaskModelFieldBuilder() {
	// TODO Auto-generated destructor stub
}

IModelFieldRoot *TaskModelFieldBuilder::build(
		IDataTypeStruct 		*type,
		const std::string		&name) {
	m_scopes.clear();
	m_name = name; // TODO:
	m_type_field = 0;
	type->accept(this);
	return dynamic_cast<IModelFieldRoot *>(m_scopes.at(0));
}

void TaskModelFieldBuilder::visitTypeField(ITypeField *f) {
	IModelFieldType *field = m_ctxt->mkModelFieldType(f);
	m_scopes.back()->addField(field);

	m_scopes.push_back(field);
	VisitorBase::visitTypeField(f);
	m_scopes.pop_back();
}

void TaskModelFieldBuilder::visitDataTypeInt(IDataTypeInt *t) {

}

void TaskModelFieldBuilder::visitDataTypeStruct(IDataTypeStruct *t) {
	IModelFieldRoot *field = m_ctxt->mkModelFieldRoot(t, m_name);

	m_scopes.push_back(field);
	VisitorBase::visitDataTypeStruct(t);

	// Leave the initial field
}


} /* namespace vsc */
