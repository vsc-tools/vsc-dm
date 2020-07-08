
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
 * RandomizerSingleSolver.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "solver/RandomizerSingleSolver.h"
#include "solver/SolveGroupSetBuilder.h"
#include "solver/FieldBoundVisitor.h"

namespace vsc {

RandomizerSingleSolver::RandomizerSingleSolver(ISolverBackend *backend) : m_backend(backend) {
	// TODO Auto-generated constructor stub

}

RandomizerSingleSolver::~RandomizerSingleSolver() {
	// TODO Auto-generated destructor stub
}

bool RandomizerSingleSolver::randomize(
			uint64_t								seed,
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintBlockSP>	&constraints) {
	m_solver = ISolverInstUP(m_backend->createSolverInst());

	FieldBoundMapUP bounds(FieldBoundVisitor().process(
			fields,
			constraints));

	for (FieldBoundMap::iterator it=bounds->begin();
			it!=bounds->end(); it++) {
		fprintf(stdout, "field %s %d\n", it->first->name().c_str(),
				static_cast<FieldScalar *>(it->first)->width());
		for (domain_t::const_iterator di=it->second->domain().begin();
				di!=it->second->domain().end(); di++) {
			fprintf(stdout, "  %lld..%lld\n",
					di->first->val_s(),
					di->second->val_s());
		}
	}

	// Build out fields
	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		m_solver->initField((*it).get());
	}

	// Build out constraints
	for (std::vector<ConstraintBlockSP>::const_iterator it=constraints.begin();
			it!=constraints.end(); it++) {
		m_solver->initConstraint((*it).get());
		m_solver->addAssert(it->get());
	}

	bool ret = m_solver->isSAT();

	fprintf(stdout, "isSAT: %d\n", ret);

	if (ret) {
		// Propagate values from the solver to the fields
		for (std::vector<FieldSP>::const_iterator it=fields.begin();
				it!=fields.end(); it++) {
			m_solver->finalizeField((*it).get());
		}
	}

	// Free the solver instance
	m_solver.reset(0);

	return ret;
}

} /* namespace vsc */
