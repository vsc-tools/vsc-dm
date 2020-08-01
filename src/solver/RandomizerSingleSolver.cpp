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
#include "expr/ExprValNumeric.h"

namespace vsc {

RandomizerSingleSolver::RandomizerSingleSolver(uint32_t seed, ISolverBackend *backend) :
		m_rng(seed),
		m_backend(backend) {
	// TODO Auto-generated constructor stub

}

RandomizerSingleSolver::~RandomizerSingleSolver() {
	// TODO Auto-generated destructor stub
}

bool RandomizerSingleSolver::randomize(
			std::initializer_list<FieldSP>			fields,
			std::initializer_list<ConstraintStmtSP>	constraints) {
	return randomize(fields, constraints);
}

bool RandomizerSingleSolver::randomize(
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintStmtSP>		&constraints) {
	RNG		rng(m_rng.next());
	std::vector<FieldScalar *> rand_fields;

	// Properly toggle the 'used_rand' flag for all top-level fields
	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->set_used_rand(true);
	}

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
	for (std::vector<Field *>::const_iterator it=solvegroups->unconstrained().begin();
			it!=solvegroups->unconstrained().end(); it++) {
		FieldScalar *fs = static_cast<FieldScalar *>(*it);
		if (fs->is_signed()) {
		} else {
			if (fs->width() > 31) {
			} else {
				fs->val(ExprValNumericSP(new ExprValNumeric(
						rng.randint_u(0, (1 << fs->width())-1),
						fs->width(),
						fs->is_signed())));
			}
		}
	}


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

	// Build out fields
	for (std::set<Field *>::const_iterator it=group->fields().begin();
			it!=group->fields().end(); it++) {
		solver->initField(*it);
	}

	// Build out and assert hard constraints
	for (std::vector<ConstraintStmt *>::const_iterator it=group->constraints().begin();
			it!=group->constraints().end(); it++) {
		solver->initConstraint(*it);
		solver->addAssert(*it);
	}


	// Handle soft constraints
	if (group->soft_constraints().size() > 0) {
		// First, build out all soft constraints
		for (std::vector<ConstraintSoft *>::const_iterator it=group->soft_constraints().begin();
				it!=group->soft_constraints().end(); it++) {
			solver->initConstraint(*it);
		}

		uint32_t soft_idx = 0;

		while (soft_idx < group->soft_constraints().size()) {
			for (uint32_t i=soft_idx; i<group->soft_constraints().size(); i++) {
				solver->addAssume(group->soft_constraints().at(i));
			}
			if (solver->isSAT()) {
				// Convert the remaining soft constraints to asserts
				for (uint32_t i=soft_idx; i<group->soft_constraints().size(); i++) {
					solver->addAssert(group->soft_constraints().at(i));
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
		if (!solver->isSAT()) {
			ret = false;;
		}
	}

	if (ret) {
		swizzle_randvars(rng, solver, group);
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
			solver->finalizeField(*it);
		}
	}


	return ret;
}

void RandomizerSingleSolver::swizzle_randvars(
		RNG						&rng,
		ISolverInstUP			&solver,
		SolveGroup				*group) {
	const std::vector<Field *> &fields = group->rand_fields();
	FieldBoundMapUP bounds(FieldBoundVisitor().process(
			group->fields(),
			group->constraints(),
			group->soft_constraints()));
	ExprSP e;

	if (fields.size() > 0) {
		uint32_t target_idx = 0;
		if (fields.size() > 1) {
			target_idx = rng.randint_u(0, fields.size()-1);
		}
		Field *target = fields.at(target_idx);

		if (bounds->find(target) != bounds->end()) {
			e = create_rand_domain_constraint(
					rng, target, bounds->find(target)->second.get());
		}
	}

	if (e.get()) {
		ConstraintExprSP c(new ConstraintExpr(e));
		solver->initConstraint(c.get());
		solver->addAssume(c.get());
		if (!solver->isSAT()) {
			solver->isSAT();
		}
	}
}

ExprSP RandomizerSingleSolver::create_rand_domain_constraint(
		RNG					&rng,
		Field				*field,
		FieldBoundInfo		*info) {
	const domain_t &domain = info->domain();
	uint32_t range_idx = rng.randint_u(0, domain.size()-1);
	const range_t &range = domain.at(range_idx);
	uint32_t range_sz = (range.second->val_u()-range.first->val_u());
	ExprSP ret;

	if (range_sz > 64) {
		// Select a style of randomization
		uint32_t r_type = rng.randint_u(0, 3);
		uint32_t single_val = rng.randint_u(
				range.first->val_u(),
				range.second->val_u());

		if (r_type >= 0 && r_type <= 2) { // range-based randomization
			uint32_t bin_sz_h = 1;
			if (range_sz/128) {
				bin_sz_h = range_sz/128;
			}

			uint64_t min, max;
			switch (r_type) {
			case 0: { // Center the selected value in the range
				if ((single_val+bin_sz_h) > range.second->val_u()) {
					// Position the target range ending at the upper end
					// of the range
					min = range.second->val_u()-2*bin_sz_h;
					max = range.second->val_u();
				} else {
					min = single_val - bin_sz_h;
					max = single_val + bin_sz_h;
				}
			} break;
			case 1: { // Bin starts at selected value
				if ((single_val+bin_sz_h) > range.second->val_u()) {
					// Position the target range ending at the upper end
					// of the range
					min = range.second->val_u()-2*bin_sz_h;
					max = range.second->val_u();
				} else {
					min = single_val;
					max = single_val + 2*bin_sz_h;
				}
			} break;
			case 2: { // Bin ends at selected value
				if (range.first->val_u()+bin_sz_h > single_val) {
					// Position the target range starting at the minimum
					min = range.first->val_u();
					max = range.first->val_u() + 2*bin_sz_h;
				} else {
					min = single_val - 2*bin_sz_h;
					max = single_val;
				}
			} break;
			}
			ret = ExprSP(new ExprBin(
					new ExprBin(
							new ExprFieldRef(field),
							BinOp_Ge,
							new ExprNumericLiteral(
									new ExprValNumeric(min, 64, false))),
					BinOp_And,
					new ExprBin(
							new ExprFieldRef(field),
							BinOp_Le,
							new ExprNumericLiteral(
									new ExprValNumeric(max, 64, false)))
					));
		} else { // Single value
			ret = ExprSP(new ExprBin(
					new ExprFieldRef(field),
					BinOp_Eq,
					new ExprNumericLiteral(
							new ExprValNumeric(single_val, 32, false))
					));
		}
	} else {
		// Small range size. Just select a single value
		uint32_t target_val = rng.randint_u(range.first->val_u(), range.second->val_u());

		fprintf(stdout, "target=%d\n", target_val);

		ret = ExprSP(new ExprBin(
				new ExprFieldRef(field),
				BinOp_Eq,
				new ExprNumericLiteral(
						new ExprValNumeric(target_val, 32, false))
				));
	}

	return ret;
}

} /* namespace vsc */
