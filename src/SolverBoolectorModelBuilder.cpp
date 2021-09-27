/*
 * SolverBoolectorModelBuilder.cpp
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include "boolector/boolector.h"
#include "SolverBoolectorModelBuilder.h"

namespace vsc {

SolverBoolectorModelBuilder::SolverBoolectorModelBuilder(
		SolverBoolector *solver) : m_solver(solver) {
	// TODO Auto-generated constructor stub

}

SolverBoolectorModelBuilder::~SolverBoolectorModelBuilder() {
	// TODO Auto-generated destructor stub
}

BoolectorNode *SolverBoolectorModelBuilder::build(ModelField *f) {
	f->accept(this);
	BoolectorSort sort = m_solver->get_sort(32);
	BoolectorNode *node = boolector_var(m_solver->btor(), sort, 0);

	return node;
}

BoolectorNode *SolverBoolectorModelBuilder::build(ModelConstraint *c) {
	return 0;
}

} /* namespace vsc */
