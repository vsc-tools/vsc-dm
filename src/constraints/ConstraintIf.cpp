/*
 * ConstraintIf.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#include "ConstraintIf.h"

namespace vsc {

ConstraintIf::ConstraintIf(
		Expr				*cond,
		ConstraintStmt		*true_s,
		ConstraintStmt		*false_s) : m_cond(cond),
				m_true_s(true_s), m_false_s(false_s) {

}

ConstraintIf::ConstraintIf(
		ExprSP				cond,
		ConstraintStmtSP	true_s,
		ConstraintStmtSP	false_s) : m_cond(cond),
				m_true_s(true_s), m_false_s(false_s) {

}

ConstraintIf::~ConstraintIf() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
