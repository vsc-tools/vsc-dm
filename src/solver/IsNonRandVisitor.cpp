/*
 * IsNonRandVisitor.cpp
 *
 *  Created on: Jul 9, 2020
 *      Author: ballance
 */

#include "IsNonRandVisitor.h"

namespace vsc {

IsNonRandVisitor::IsNonRandVisitor() : m_is_nonrand(true) {
	// TODO Auto-generated constructor stub

}

IsNonRandVisitor::~IsNonRandVisitor() {
	// TODO Auto-generated destructor stub
}

bool IsNonRandVisitor::is_nonrand(const ExprSP &expr) {
	m_is_nonrand = true;
	expr->accept(this);

	return m_is_nonrand;
}

void IsNonRandVisitor::visitExprFieldRef(ExprFieldRef *e) {
	if (e->field()->used_rand()) {
		// Definitely references a random field
		m_is_nonrand = false;
	}
}

} /* namespace vsc */
