/*
 * ISolverBackend.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_ISOLVERBACKEND_H_
#define SRC_SOLVER_ISOLVERBACKEND_H_
#include <memory>
#include <vector>
#include "ISolverData.h"
#include "ConstraintBlock.h"

namespace vsc {

class Field;

class ISolverBackend {
public:
	virtual ~ISolverBackend() { }

	// Get a solver instance
	virtual ISolverData *createSolverInst() = 0;

	// Creates solver data for a field
	virtual ISolverData *createFieldInst(
			ISolverData 		*solver,
			Field 				*f) = 0;

	// Creates solver data for a constraint
	virtual ISolverData* createConstraintInst(
			ISolverData			*solver,
			ConstraintBlock		*constraint) = 0;

	virtual void addAssume(
			ISolverData			*solver,
			ISolverData			*constraint) = 0;

	virtual void addAssert(
			ISolverData			*solver,
			ISolverData			*constraint) = 0;

	virtual bool failed(
			ISolverData			*solver,
			ISolverData			*constraint) = 0;

	virtual bool isSAT(ISolverData *solver) = 0;

};

typedef std::unique_ptr<ISolverBackend> ISolverBackendUP;

}




#endif /* SRC_SOLVER_ISOLVERBACKEND_H_ */
