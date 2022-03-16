/*
 * SolverFactoryDefault.h
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/ISolverFactory.h"

namespace vsc {

class SolverFactoryDefault : public ISolverFactory {
public:
	SolverFactoryDefault();

	virtual ~SolverFactoryDefault();

	virtual ISolver *createSolverInst(SolveSet *sset) override;

	static ISolverFactory *inst();

private:
	static SolverFactoryDefault			m_inst;

};

} /* namespace vsc */

