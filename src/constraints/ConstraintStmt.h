/*
 * ConstraintStmt.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_CONSTRAINTS_CONSTRAINTSTMT_H_
#define SRC_CONSTRAINTS_CONSTRAINTSTMT_H_
#include <memory>
#include "IVisitor.h"
#include "solver/ISolverData.h"

namespace vsc {

class ConstraintStmt {
public:
	ConstraintStmt();

	virtual ~ConstraintStmt();

	ISolverData *solver_data() const { return m_solver_data.get(); }

	void solver_data(ISolverData *sd) { m_solver_data = ISolverDataUP(sd); }

	virtual void accept(IVisitor *v) = 0;

private:
	ISolverDataUP				m_solver_data;

};

typedef std::shared_ptr<ConstraintStmt> ConstraintStmtSP;

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTSTMT_H_ */
