/*
 * SolverBackendBoolector.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_SOLVERBACKENDBOOLECTOR_H_
#define SRC_SOLVER_SOLVERBACKENDBOOLECTOR_H_
#include "ISolverBackend.h"

namespace vsc {

class SolverBackendBoolector : public virtual ISolverBackend {
public:
	SolverBackendBoolector();

	virtual ~SolverBackendBoolector();

	virtual ISolverData *createSolverInst();

	// Creates solver data for a field
	virtual ISolverData *createFieldInst(
			ISolverData 		*solver,
			Field 				*f);

	// Creates solver data for a constraint
	virtual ISolverData* createConstraintInst(
			ISolverData			*solver,
			ConstraintBlock		*constraint);

	virtual void addAssume(
			ISolverData			*solver,
			ISolverData			*constraint);

	virtual void addAssert(
			ISolverData			*solver,
			ISolverData			*constraint);

	virtual bool failed(
			ISolverData			*solver,
			ISolverData			*constraint);

	virtual bool isSAT(ISolverData *solver);

private:

};

} /* namespace vsc */

#endif /* SRC_SOLVER_SOLVERBACKENDBOOLECTOR_H_ */
