/*
 * FieldSolveDataBuilder.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "VisitorBase.h"
#include "solver/ISolverInst.h"

namespace vsc {

/**
 * Builds solve data for each field, and adds any
 * domain constraints -- eg for enum-type fields
 */
class FieldSolveDataBuilder : public VisitorBase {
public:
	FieldSolveDataBuilder(ISolverInst *inst);

	virtual ~FieldSolveDataBuilder();

	virtual void visitFieldScalar(FieldScalar *f) override;

private:
	ISolverInst				*m_inst;


};

} /* namespace vsc */

