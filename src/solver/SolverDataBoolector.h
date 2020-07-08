/*
 * SolverDataBoolector.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "boolector/boolector.h"
#include "solver/ISolverData.h"

namespace vsc {

class SolverDataBoolector : public ISolverData {
public:
	SolverDataBoolector(BoolectorNode *node);

	virtual ~SolverDataBoolector();

	BoolectorNode *node() const { return m_node; }

private:
	BoolectorNode			*m_node;
};

} /* namespace vsc */

