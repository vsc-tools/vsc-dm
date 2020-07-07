/*
 * SolveGroup.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_SOLVEGROUP_H_
#define SRC_SOLVER_SOLVEGROUP_H_
#include <memory>
#include <set>
#include "datamodel/Field.h"

namespace vsc {

/**
 * A SolveGroup captures a set of related fields and
 * constraints
 */
class SolveGroup {
public:
	SolveGroup();

	virtual ~SolveGroup();

	const std::set<Field *> &fields() const {
		return m_field_s;
	}

	const std::set<ConstraintStmt *> &constraints() const {
		return m_constraint_s;
	}

	bool addConstraint(ConstraintStmt *c) {
		return m_constraint_s.insert(c).second;
	}

	bool addField(Field *f) {
		return m_field_s.insert(f).second;
	}

private:
	std::set<Field *>				m_field_s;
	std::set<ConstraintStmt *>		m_constraint_s;
};

typedef std::unique_ptr<SolveGroup> SolveGroupUP;

} /* namespace vsc */

#endif /* SRC_SOLVER_SOLVEGROUP_H_ */
