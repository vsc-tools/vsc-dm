/*
 * Randomizer.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */
#pragma once
#include "vsc/IModelConstraint.h"
#include "vsc/ISolverFactory.h"
#include "ModelField.h"
#include "vsc/IRandomizer.h"
#include "vsc/IRandState.h"
#include "RNG.h"

namespace vsc {

class Randomizer : public IRandomizer {
public:
	Randomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate);

	virtual ~Randomizer();

	virtual bool randomize(
			const std::vector<IModelField *>		&fields,
			const std::vector<IModelConstraint *>	&constraints,
			bool									diagnose_failures
			) override;

private:
	ISolverFactory		*m_solver_factory;
	IRandState			*m_randstate;

};

} /* namespace vsc */

