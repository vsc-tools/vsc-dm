/*
 * SolveSpec.cpp
 *
 *  Created on: Oct 7, 2021
 *      Author: mballance
 */

#include "SolveSpec.h"

namespace vsc {

SolveSpec::SolveSpec(
		const std::vector<SolveSet *>		&solvesets,
		const std::vector<ModelField *>		&unconstrained) :
				m_unconstrained(unconstrained) {

	for (auto it=solvesets.begin(); it!=solvesets.end(); it++) {
		m_solvesets.push_back(SolveSetUP(*it));
	}


}

SolveSpec::~SolveSpec() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
