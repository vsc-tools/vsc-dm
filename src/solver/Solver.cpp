/*
 * Solver.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#include "Solver.h"
#include "SolverBackendBoolector.h"

namespace vsc {

Solver::Solver(ISolverBackend *backend) : m_backend(backend) {
	// TODO Auto-generated constructor stub

}

Solver::~Solver() {
	// TODO Auto-generated destructor stub
}

bool Solver::randomize(
		uint64_t								seed,
		const std::vector<FieldSP>				&fields,
		const std::vector<ConstraintBlockSP>	&constraints) {
	return true;
}

bool Solver::sat(
		const std::vector<FieldSP>				&fields,
		const std::vector<ConstraintBlockSP>	&constraints) {
	return true;
}

Solver *Solver::inst() {
	if (!m_inst.get()) {
		m_inst = SolverUP(new Solver(new SolverBackendBoolector()));
	}

	return m_inst.get();
}

SolverUP Solver::m_inst;

} /* namespace vsc */
