/*
 * constraint_implies.cpp
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#include "constraint_implies.h"
#include "ctor.h"
#include "ModelConstraintImplies.h"

namespace vsc {
namespace facade {

constraint_implies::constraint_implies(
		const expr_base						&cond,
		const std::function<void()>		&body,
		const char						*file,
		int32_t							lineno) {
	IModelExpr *cond_e = ctor::inst()->pop_expr();
	ModelConstraintScope *body_c = new ModelConstraintScope();
	ModelConstraintImplies *c = new ModelConstraintImplies(
			cond_e,
			body_c);
	ctor::inst()->push_constraint_scope(body_c);
	body();
	ctor::inst()->pop_constraint_scope();
}

constraint_implies::~constraint_implies() {
	// TODO Auto-generated destructor stub
}

} /* namespace facade */
} /* namespace vsc */
