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

namespace vsc {

class ConstraintStmt {
public:
	ConstraintStmt();

	virtual ~ConstraintStmt();

	virtual void accept(IVisitor *v) = 0;
};

typedef std::shared_ptr<ConstraintStmt> ConstraintStmtSP;

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTSTMT_H_ */
