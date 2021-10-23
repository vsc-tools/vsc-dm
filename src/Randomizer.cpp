/*
 * Randomizer.cpp
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include "Randomizer.h"
#include "SolveSpecBuilder.h"

namespace vsc {

Randomizer::Randomizer(RNG &rng) : m_rng(rng) {
	// TODO Auto-generated constructor stub

}

Randomizer::~Randomizer() {
	// TODO Auto-generated destructor stub
}

bool Randomizer::randomize(
			const std::vector<ModelField *>			&fields,
			const std::vector<ModelConstraint *>	&constraints,
			bool									diagnose_failures
			) {
	SolveSpecUP spec(SolveSpecBuilder().build(
			fields,
			constraints
			));

	return true;
}

} /* namespace vsc */
