/*
 * Randomizer.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */
#pragma once
#include "ModelField.h"
#include "ModelConstraint.h"
#include "RNG.h"

namespace vsc {

class Randomizer {
public:
	Randomizer(RNG &rng);

	virtual ~Randomizer();

	bool randomize(
			const std::vector<ModelField *>			&fields,
			const std::vector<ModelConstraint *>	&constraints,
			bool									diagnose_failures
			);

private:
	RNG				&m_rng;

};

} /* namespace vsc */

