
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
 * SolverInstBoolector.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "SolverBoolector.h"
#include "boolector/boolector.h"


namespace vsc {

SolverBoolector::SolverBoolector() {
	m_btor = boolector_new();
	boolector_set_opt(m_btor, BTOR_OPT_INCREMENTAL, 1);
	boolector_set_opt(m_btor, BTOR_OPT_MODEL_GEN, 1);

#ifdef UNDEFINED
	m_op = Op_CreateField; // throwaway
	m_node = 0;
	m_is_signed = false;
#endif
}

SolverBoolector::~SolverBoolector() {
	boolector_release_all(m_btor);
	boolector_delete(m_btor);

#ifdef UNDEFINED
	/*
	for (std::map<uint32_t,BoolectorSort>::iterator it=m_sort_m.begin();
			it!=m_sort_m.end(); it++) {
		boolector_release)
	}
	 */
#endif
}

	// Creates solver data for a field
void SolverBoolector::initField(ModelField *f) {
	// TODO:
}

	// Creates solver data for a constraint
void SolverBoolector::initConstraint(ModelConstraint *c) {
	// TODO:
}

void SolverBoolector::addAssume(ModelConstraint *c) {
#ifdef UNDEFINED
	boolector_assume(m_btor,
			static_cast<SolverDataBoolector *>(c->solver_data())->node());
#endif
}

void SolverBoolector::addAssert(ModelConstraint *c) {
#ifdef UNDEFINED
	boolector_assert(m_btor,
			static_cast<SolverDataBoolector *>(c->solver_data())->node());
#endif
}

bool SolverBoolector::isSAT() {
#ifdef UNDEFINED
	int res = boolector_sat(m_btor);

	return (res == BTOR_RESULT_SAT);
#endif
}

void SolverBoolector::finalizeField(ModelField *f) {
	// TODO:
}

} /* namespace vsc */
