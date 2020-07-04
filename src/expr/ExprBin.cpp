/*
 * ExprBin.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#include "ExprBin.h"

namespace vsc {

ExprBin::ExprBin(
		Expr			*lhs,
		ExprBinOp		op,
		Expr			*rhs) : m_lhs(lhs), m_op(op), m_rhs(rhs) {
	// TODO Auto-generated constructor stub

}

ExprBin::~ExprBin() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
