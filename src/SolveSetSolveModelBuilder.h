/*
 * SolveSetSolveModelBuilder.h
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/ISolver.h"
#include "SolveSet.h"
#include "vsc/impl/VisitorBase.h"

namespace vsc {

/**
 * Builds solver data for the fields and constraints in the
 * specified solve set
 */
class SolveSetSolveModelBuilder : public VisitorBase {
public:
	SolveSetSolveModelBuilder(ISolver *solver);

	virtual ~SolveSetSolveModelBuilder();

	void build(SolveSet *sset);

private:
	ISolver						*m_solver;

};

} /* namespace vsc */

