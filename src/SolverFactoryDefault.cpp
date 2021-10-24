/*
 * SolverFactoryDefault.cpp
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#include "SolverFactoryDefault.h"
#include "SolverBitwuzla.h"
#include "SolverBoolector.h"

namespace vsc {

SolverFactoryDefault::SolverFactoryDefault() {
	// TODO Auto-generated constructor stub

}

SolverFactoryDefault::~SolverFactoryDefault() {
	// TODO Auto-generated destructor stub
}

ISolver *SolverFactoryDefault::createSolverInst(SolveSet *sset) {
//	return new SolverBitwuzla();
	return new SolverBoolector();
}

} /* namespace vsc */
