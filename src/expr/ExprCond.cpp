/*
 * ExprCond.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#include "ExprCond.h"

namespace vsc {

ExprCond::ExprCond(
		Expr		*cond,
		Expr		*true_e,
		Expr		*false_e) : m_cond(cond),
				m_true_e(true_e), m_false_e(false_e) {

}

ExprCond::~ExprCond() {
	// TODO Auto-generated destructor stub
}

} /* namespace vsc */
