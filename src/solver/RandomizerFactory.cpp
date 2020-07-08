/*
 * RandomizerFactory.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#include "solver/RandomizerFactory.h"
#include "solver/SolverBackendBoolector.h"
#include "solver/RandomizerSingleSolver.h"

namespace vsc {

RandomizerFactory::RandomizerFactory() {
	// TODO Auto-generated constructor stub

}

RandomizerFactory::~RandomizerFactory() {
	// TODO Auto-generated destructor stub
}

IRandomizer *RandomizerFactory::inst() {
	if (!m_inst.get()) {
		m_inst = IRandomizerUP(new RandomizerSingleSolver(
				new SolverBackendBoolector()));
	}
	return m_inst.get();
}

IRandomizerUP RandomizerFactory::m_inst;

} /* namespace vsc */
