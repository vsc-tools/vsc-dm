/*
 * Solver.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_SOLVER_H_
#define SRC_SOLVER_SOLVER_H_
#include <stdint.h>
#include <vector>
#include "Field.h"
#include "ConstraintBlock.h"
#include "ISolverBackend.h"

namespace vsc {

class Solver;
typedef std::unique_ptr<Solver> SolverUP;

class Solver {
public:
	Solver(ISolverBackend *backend);

	virtual ~Solver();

	virtual bool randomize(
			uint64_t								seed,
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintBlockSP>	&constraints
			);

	virtual bool sat(
			const std::vector<FieldSP>				&fields,
			const std::vector<ConstraintBlockSP>	&constraints);

	static Solver *inst();

private:
	ISolverBackendUP			m_backend;
	static SolverUP				m_inst;
};


} /* namespace vsc */

#endif /* SRC_SOLVER_SOLVER_H_ */
