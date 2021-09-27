/*
 * SolverBoolectorModelBuilder.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#include "SolverBoolector.h"
#include "VisitorBase.h"

namespace vsc {

class SolverBoolectorModelBuilder : public VisitorBase {
public:
	SolverBoolectorModelBuilder(SolverBoolector *solver);

	virtual ~SolverBoolectorModelBuilder();

	BoolectorNode *build(ModelField *f);

	BoolectorNode *build(ModelConstraint *c);

private:
	SolverBoolector					*m_solver;
};

} /* namespace vsc */

