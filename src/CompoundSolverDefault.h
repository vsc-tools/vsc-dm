/*
 * CompoundSolverDefault.h
 *
 *  Created on: Mar 23, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ICompoundSolver.h"

namespace vsc {

class CompoundSolverDefault : public ICompoundSolver {
public:
	CompoundSolverDefault();

	virtual ~CompoundSolverDefault();

	virtual bool solve(
			IRandState								*randstate,
			const std::vector<IModelField *>		&fields,
			const std::vector<IModelConstraint *>	&constraints,
			SolveFlags								flags) override;
};

} /* namespace vsc */

