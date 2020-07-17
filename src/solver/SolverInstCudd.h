/*
 * SolverInstCudd.h
 *
 *  Created on: Jul 14, 2020
 *      Author: ballance
 */

#pragma once
#include "ISolverInst.h"

namespace vsc {

class SolverInstCudd : public ISolverInst {
public:
	SolverInstCudd();

	virtual ~SolverInstCudd();

	// Creates solver data for a field
	virtual void initField(Field *f) override;

	// Creates solver data for a constraint
	virtual void initConstraint(ConstraintStmt *c) override;

	virtual void addAssume(ConstraintStmt *c) override;

	virtual void addAssert(ConstraintStmt *c) override;

	virtual bool failed(ConstraintStmt *c) override;

	virtual bool isSAT() override;

	// Assign values to field
	virtual void finalizeField(Field *f) override;


};

} /* namespace vsc */

