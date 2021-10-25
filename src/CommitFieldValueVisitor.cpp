/*
 * CommitFieldValueVisitor.cpp
 *
 *  Created on: Oct 24, 2021
 *      Author: mballance
 */

#include "CommitFieldValueVisitor.h"

namespace vsc {

CommitFieldValueVisitor::CommitFieldValueVisitor(ISolver *solver) :
	m_solver(solver) {
	// TODO Auto-generated constructor stub

}

CommitFieldValueVisitor::~CommitFieldValueVisitor() {
	// TODO Auto-generated destructor stub
}

void CommitFieldValueVisitor::commit(ModelField *f) {
	f->accept(this);
}

void CommitFieldValueVisitor::visitDataTypeInt(DataTypeInt *t) {

}

void CommitFieldValueVisitor::visitModelField(ModelField *f) {
	m_solver->setFieldValue(f);
}

} /* namespace vsc */
