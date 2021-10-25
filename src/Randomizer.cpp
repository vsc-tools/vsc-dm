/*
 * Randomizer.cpp
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include "CommitFieldValueVisitor.h"
#include "Debug.h"
#include "Randomizer.h"
#include "SolveSpecBuilder.h"
#include "SolveSetSolveModelBuilder.h"

#undef EN_DEBUG_RANDOMIZER

#ifdef EN_DEBUG_RANDOMIZER
DEBUG_SCOPE(Randomizer)
#define DEBUG_ENTER(fmt, ...) DEBUG_ENTER_BASE(Randomizer, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) DEBUG_LEAVE_BASE(Randomizer, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) DEBUG_BASE(Randomizer, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {

Randomizer::Randomizer(
		ISolverFactory		*solver_factory,
		RNG 				&rng) : m_solver_factory(solver_factory), m_rng(rng) {
	// TODO Auto-generated constructor stub

}

Randomizer::~Randomizer() {
	// TODO Auto-generated destructor stub
}

bool Randomizer::randomize(
			const std::vector<ModelField *>			&fields,
			const std::vector<ModelConstraint *>	&constraints,
			bool									diagnose_failures) {
	bool ret = true;
	DEBUG_ENTER("randomize n_fields=%d n_constraints=%d",
			fields.size(),
			constraints.size());
	SolveSpecUP spec(SolveSpecBuilder().build(
			fields,
			constraints
			));

	for (auto sset=spec->solvesets().begin();
			sset!=spec->solvesets().end(); sset++) {
		ISolverUP solver(m_solver_factory->createSolverInst(sset->get()));

		// Build solve data for this solve set
		SolveSetSolveModelBuilder(solver.get()).build(sset->get());

		// First, ensure all constraints solve
		for (auto c_it=(*sset)->constraints().begin();
				c_it!=(*sset)->constraints().end(); c_it++) {
			solver->addAssume(*c_it);
		}
		for (auto c_it=(*sset)->soft_constraints().begin();
				c_it!=(*sset)->soft_constraints().end(); c_it++) {
			solver->addAssume(*c_it);
		}

		if (solver->isSAT()) {
			DEBUG("PASS: Initial try-solve for solveset");
			for (auto f_it=(*sset)->rand_fields().begin();
					f_it!=(*sset)->rand_fields().end(); f_it++) {
				DEBUG("Commit %s", (*f_it)->name().c_str());
				CommitFieldValueVisitor(solver.get()).commit(*f_it);
			}
		} else {
			DEBUG("FAIL: Initial try-solve for solveset");

			// Try backing off soft constraints

			ret = false;
			break;
		}
	}

	for (auto uc_it=spec->unconstrained().begin();
			uc_it!=spec->unconstrained().end(); uc_it++) {
		DEBUG("Randomize unconstrained field %s", (*uc_it)->name().c_str());
	}

	DEBUG_LEAVE("randomize n_fields=%d n_constraints=%d ret=%d",
			fields.size(),
			constraints.size(),
			ret);
	return ret;
}

} /* namespace vsc */
