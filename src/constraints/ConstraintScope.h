/*
 * ConstraintScope.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_CONSTRAINTS_CONSTRAINTSCOPE_H_
#define SRC_CONSTRAINTS_CONSTRAINTSCOPE_H_
#include <vector>
#include "constraints/ConstraintStmt.h"

namespace vsc {

class ConstraintScope : public ConstraintStmt {
public:
	ConstraintScope();

	ConstraintScope(
			std::initializer_list<ConstraintStmt *> stmts);

	virtual ~ConstraintScope();

	const std::vector<ConstraintStmtSP> &constraints() const {
		return m_constraints;
	}

	void addConstraint(ConstraintStmt *c) {
		m_constraints.push_back(ConstraintStmtSP(c));
	}

	void addConstraint(ConstraintStmtSP c) {
		m_constraints.push_back(c);
	}

	virtual void accept(IVisitor *v) { v->visitConstraintScope(this); }

private:
	std::vector<ConstraintStmtSP>		m_constraints;
};

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTSCOPE_H_ */
