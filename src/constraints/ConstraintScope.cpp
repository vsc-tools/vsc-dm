/*
 * ConstraintScope.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#include "ConstraintScope.h"

namespace vsc {

ConstraintScope::ConstraintScope() {
	// TODO Auto-generated constructor stub

}

ConstraintScope::ConstraintScope(
		std::initializer_list<ConstraintStmt *> stmts) {
	for (std::initializer_list<ConstraintStmt *>::iterator it=stmts.begin();
			it!=stmts.end(); it++) {
		m_constraints.push_back(ConstraintStmtSP(*it));
	}
}

ConstraintScope::~ConstraintScope() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
