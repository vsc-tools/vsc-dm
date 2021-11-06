/*
 * expr_range.cpp
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#include "ctor.h"
#include "expr_range.h"
#include "ModelExprRange.h"

namespace vsc {
namespace facade {

expr_range::expr_range(
		const expr			&val) {
	ctor::inst()->pop_expr();
	m_core = new ModelExprRange(val.core(), 0);
}

expr_range::expr_range(
		const expr			&lower,
		const expr			&upper) {
	ctor::inst()->pop_expr();
	ctor::inst()->pop_expr();
	m_core = new ModelExprRange(lower.core(), upper.core());
}

expr_range::~expr_range() {
	// TODO Auto-generated destructor stub
}

} /* namespace facade */
} /* namespace vsc */
