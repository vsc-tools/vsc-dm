
/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * SolverBackendBoolector.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#include "SolverBackendBoolector.h"
#include "boolector/boolector.h"

namespace vsc {

class BoolectorSolverInst : public ISolverData {
public:

	BoolectorSolverInst() {
		m_btor = boolector_new();
		boolector_set_opt(m_btor, BTOR_OPT_INCREMENTAL, 1);
		boolector_set_opt(m_btor, BTOR_OPT_MODEL_GEN, 1);
	}

	virtual ~BoolectorSolverInst() {
		boolector_delete(m_btor);
	}

private:
	Btor				*m_btor;
};

SolverBackendBoolector::SolverBackendBoolector() {
	// TODO Auto-generated constructor stub

}

SolverBackendBoolector::~SolverBackendBoolector() {
	// TODO Auto-generated destructor stub
}

ISolverData *SolverBackendBoolector::createSolverInst() {
	return new BoolectorSolverInst();
}

// Creates solver data for a field
ISolverData *SolverBackendBoolector::createFieldInst(
		ISolverData 		*solver,
		Field 				*f) {
	return 0;
}

// Creates solver data for a constraint
ISolverData* SolverBackendBoolector::createConstraintInst(
		ISolverData			*solver,
		ConstraintBlock		*constraint) {
	return 0;
}

void SolverBackendBoolector::addAssume(
		ISolverData			*solver,
		ISolverData			*constraint) {

}

void SolverBackendBoolector::addAssert(
		ISolverData			*solver,
		ISolverData			*constraint) {

}

bool SolverBackendBoolector::failed(
		ISolverData			*solver,
		ISolverData			*constraint) {
	return true;
}

bool SolverBackendBoolector::isSAT(ISolverData *solver) {
	return false;
}

} /* namespace vsc */
