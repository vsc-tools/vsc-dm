/*
 * SolverInstBoolector.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#pragma once
#include <map>
#include "boolector/boolector.h"
#include "solver/ISolverInst.h"
#include "VisitorBase.h"

namespace vsc {

class SolverInstBoolector : public VisitorBase, public virtual ISolverInst {
public:
	SolverInstBoolector();

	virtual ~SolverInstBoolector();

	// Creates solver data for a field (and possibly sub-fields)
	virtual void initField(Field *f) override;

	// Creates solver data for a constraint
	virtual void initConstraint(ConstraintStmt *c) override;

	virtual void addAssume(ConstraintStmt *c) override;

	virtual void addAssert(ConstraintStmt *c) override;

	virtual bool failed(ConstraintStmt *c) override;

	virtual bool isSAT() override;

	virtual void finalizeField(Field *f) override;

	/**
	 * Visitor methods to support constraint construction
	 */
	virtual void visitFieldScalar(FieldScalar *f) override;

private:
	enum SolverOp {
		Op_CreateField,
		Op_CreateConstraint,
		Op_FinalizeField
	};

private:
	BoolectorSort get_sort(int32_t width);

private:
	Btor								*m_btor;
	SolverOp							m_op;
	BoolectorNode						*m_node;
	std::map<uint32_t, BoolectorSort>	m_sort_m;

};

} /* namespace vsc */

