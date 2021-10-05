/*
 * expr.cpp
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#include "expr.h"

namespace vsc {
namespace facade {

expr::expr(const attr_scalar &attr) : m_fieldref(&attr) {
	// TODO Auto-generated constructor stub

}

expr::expr(
			const expr		&lhs,
			const expr		&rhs) : m_fieldref(0) {
	;
}


expr::~expr() {
	// TODO Auto-generated destructor stub
}

/*
expr expr::operator == (int32_t v) {
	;
}
 */

} /* namespace facade */
} /* namespace vsc */
