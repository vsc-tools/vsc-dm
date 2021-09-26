/*
 * Randomizer.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */
#pragma once
#include "ModelField.h"
#include "ModelConstraint.h"

namespace vsc {

class Randomizer {
public:
	Randomizer();

	virtual ~Randomizer();

	bool randomize(
			const std::vector<ModelField *>			&fields,
			const std::vector<ModelConstraint *>	&constraints,
			bool									diagnose_failures
			);


};

} /* namespace vsc */

