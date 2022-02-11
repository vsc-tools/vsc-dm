/*
 * Copyright 2019-2021 Matthew Ballance and contributors
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

void CommitFieldValueVisitor::commit(IModelField *f) {
	f->accept(this);
}

void CommitFieldValueVisitor::visitDataTypeInt(IDataTypeInt *t) {

}

void CommitFieldValueVisitor::visitModelField(IModelField *f) {
	m_solver->setFieldValue(f);
}

} /* namespace vsc */
