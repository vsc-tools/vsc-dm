/*
 * RandomizerSingleSolver.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "solver/RandomizerSingleSolver.h"
#include "solver/SolveGroupSetBuilder.h"

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

	// Build out fields
	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		m_solver->initField((*it).get());
	}

	// Build out constraints
	for (std::vector<ConstraintBlockSP>::const_iterator it=constraints.begin();
			it!=constraints.end(); it++) {
		m_solver->initConstraint((*it).get());
	}

	bool ret = m_solver->isSAT();

	if (ret) {
		// Propagate values from the solver to the fields
		for (std::vector<FieldSP>::const_iterator it=fields.begin();
				it!=fields.end(); it++) {
			m_solver->finalizeField((*it).get());
		}
	}

	// Free the solver instance
	m_solver.release();

	return ret;
}

} /* namespace vsc */
