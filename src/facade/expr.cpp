/*
 * expr.cpp
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#include "attr_scalar.h"
#include "ctor.h"
#include "expr.h"
#include "ModelExprFieldRef.h"

namespace vsc {
namespace facade {

expr::expr(const attr_scalar &attr) :
		m_core(new ModelExprFieldRef(attr.field())) {
	ctor::inst()->push_expr(m_core);

}

expr::expr(ModelExpr *core) : m_core(core) {
	ctor::inst()->push_expr(m_core);
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
