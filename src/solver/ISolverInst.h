/*
 * ISolverInst.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include "solver/ISolverData.h"
#include "datamodel/Field.h"
#include "constraints/ConstraintStmt.h"

namespace vsc {

/**
 * Represents an instance of a backend solver
 */
class ISolverInst {
public:

	virtual ~ISolverInst() { }

	// Creates solver data for a field
	virtual void initField(Field *f) = 0;

	// Creates solver data for a constraint
	virtual void initConstraint(ConstraintStmt *c) = 0;

	virtual void addAssume(ConstraintStmt *c) = 0;

	virtual void addAssert(ConstraintStmt *c) = 0;

	virtual bool failed(ConstraintStmt *c) = 0;

	virtual bool isSAT() = 0;

	// Assign values to field
	virtual void finalizeField(Field *f) = 0;

};

typedef std::unique_ptr<ISolverInst> ISolverInstUP;

}



