/*
 * SolveSetSolveModelBuilder.cpp
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#include "SolveSetSolveModelBuilder.h"

namespace vsc {

SolveSetSolveModelBuilder::SolveSetSolveModelBuilder(ISolver *solver) :
		m_solver(solver) {
	// TODO Auto-generated constructor stub

}

SolveSetSolveModelBuilder::~SolveSetSolveModelBuilder() {
	// TODO Auto-generated destructor stub
}

void SolveSetSolveModelBuilder::build(SolveSet *sset) {
	for (auto f_it=sset->rand_fields().begin();
			f_it!=sset->rand_fields().end(); f_it++) {
		m_solver->initField(*f_it);
	}
	for (auto c_it=sset->constraints().begin();
			c_it!=sset->constraints().end(); c_it++) {
		m_solver->initConstraint(*c_it);
	}
}

} /* namespace vsc */
