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
#include "solver/RandFieldCollector.h"

namespace vsc {

RandomizerSingleSolver::RandomizerSingleSolver(ISolverBackend *backend) : m_backend(backend) {
	// TODO Auto-generated constructor stub

}

RandomizerSingleSolver::~RandomizerSingleSolver() {
	// TODO Auto-generated destructor stub
}

bool RandomizerSingleSolver::randomize(
			uint32_t								seed,
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintBlockSP>	&constraints) {
	RNG		rng(seed);
	std::vector<FieldScalar *> rand_fields;

	RandFieldCollector().collect(fields, rand_fields);

	// Build an initial bounds map, for use in appropriately sizing arrays
	FieldBoundMapUP bounds(FieldBoundVisitor().process(
			fields,
			constraints));

	// TODO: size arrays, and build out synthetic constraints
	// TODO: size arrays, and build out synthetic constraints

	// TODO: construct solve groups
	SolveGroupSetUP solvegroups(SolveGroupSetBuilder().build(
			fields, constraints));

	// First, randomize each solvegroup
	for (std::vector<SolveGroupUP>::const_iterator it=solvegroups->solvegroups().begin();
			it!=solvegroups->solvegroups().end(); it++) {
		randomize_solvegroup(rng, (*it).get());
	}

	// TOOD: Assign random values to unconstrained fields


//	for (FieldBoundMap::iterator it=bounds->begin();
//			it!=bounds->end(); it++) {
//		fprintf(stdout, "field %s %d\n", it->first->name().c_str(),
//				static_cast<FieldScalar *>(it->first)->width());
//		for (domain_t::const_iterator di=it->second->domain().begin();
//				di!=it->second->domain().end(); di++) {
//			fprintf(stdout, "  %lld..%lld\n",
//					di->first->val_s(),
//					di->second->val_s());
//		}
//	}



	return true;
}

bool RandomizerSingleSolver::randomize_solvegroup(
		RNG					&rng,
		SolveGroup			*group) {
	ISolverInstUP solver(m_backend->createSolverInst());
	bool ret = true;
	bool need_solve = true;

	// Build detailed bounds information for the fields in this solvegroup
	FieldBoundMapUP bounds(FieldBoundVisitor().process(
			group->fields(),
			group->constraints(),
			group->soft_constraints()));

	// Build out fields
	for (std::set<Field *>::const_iterator it=group->fields().begin();
			it!=group->fields().end(); it++) {
		m_solver->initField(*it);
	}

	// Build out and assert hard constraints
	for (std::vector<ConstraintStmt *>::const_iterator it=group->constraints().begin();
			it!=group->constraints().end(); it++) {
		m_solver->initConstraint(*it);
		m_solver->addAssert(*it);
	}


	// Handle soft constraints
	if (group->soft_constraints().size() > 0) {
		// First, build out all soft constraints
		for (std::vector<ConstraintSoft *>::const_iterator it=group->soft_constraints().begin();
				it!=group->soft_constraints().end(); it++) {
			m_solver->initConstraint(*it);
		}

		uint32_t soft_idx = 0;

		while (soft_idx < group->soft_constraints().size()) {
			for (uint32_t i=soft_idx; i<group->soft_constraints().size(); i++) {
				m_solver->addAssume(group->soft_constraints().at(i));
			}
			if (m_solver->isSAT()) {
				// Convert the remaining soft constraints to asserts
				for (uint32_t i=soft_idx; i<group->soft_constraints().size(); i++) {
					m_solver->addAssert(group->soft_constraints().at(i));
				}
				// Must solve again prior to fixing values
				need_solve = true;
				ret = true;
				break;
			} else {
				ret = false;
				need_solve = false;
			}

			soft_idx++;
		}
	}

	// Solve to ensure we have a valid constraint problem prior to randomization
	if (need_solve) {
		if (!m_solver->isSAT()) {
			ret = false;;
		}
	}

	if (ret) {
		swizzle_randvars(rng, group);
	}

//	if (!ret) {
//		// TODO: retry if soft constraints are in play
//	} else {
//		// Convert all assumptions to assertions
//		for (std::vector<ConstraintBlockSP>::const_iterator it=constraints.begin();
//				it!=constraints.end(); it++) {
//			m_solver->initConstraint((*it).get());
//			m_solver->addAssert(it->get());
//		}
//	}
//
//	// TODO: swizzle randvars
//	ret = m_solver->isSAT();

	// Finally, propagate values to the randomized fields
	if (ret) {
		// Propagate values from the solver to the fields
		for (std::vector<Field *>::const_iterator it=group->rand_fields().begin();
				it!=group->rand_fields().end(); it++) {
			m_solver->finalizeField(*it);
		}
	}


	return ret;
}

} /* namespace vsc */
