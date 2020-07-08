/*
 * RandomizerSingleSolver.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "solver/IRandomizer.h"
#include "solver/ISolverBackend.h"

namespace vsc {

class RandomizerSingleSolver : public IRandomizer {
public:
	RandomizerSingleSolver(ISolverBackend *backend);

	virtual ~RandomizerSingleSolver();

	virtual bool randomize(
			uint64_t								seed,
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintBlockSP>	&constraints);

private:
	ISolverBackendUP					m_backend;
	ISolverInstUP						m_solver;

};

} /* namespace vsc */

