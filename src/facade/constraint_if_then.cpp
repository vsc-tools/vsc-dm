/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * if_then.cpp
 *
 *  Created on: Aug 12, 2021
 *      Author: mballance
 */

#include "constraint_if_then.h"
#include "ctor.h"

#undef if_then
#undef else_if
#undef else_then

namespace vsc {
namespace facade {

constraint_if_then::constraint_if_then(
		const expr_base						&cond,
		const std::function<void()>		&body,
		const char						*file,
		int32_t							lineno) {
	ModelConstraintScope *true_c = new ModelConstraintScope();
	m_constraint = new ModelConstraintIf(
			ctor::inst()->pop_expr(),
			true_c,
			0);
	ctor::inst()->constraint_scope()->add_constraint(m_constraint);
	ctor::inst()->push_constraint_scope(true_c);
	body();
	ctor::inst()->pop_constraint_scope();
}

constraint_if_then::constraint_if_then(
		ModelConstraintIf				*if_c) : m_constraint(if_c) {

}

constraint_if_then::~constraint_if_then() {
}

constraint_if_then constraint_if_then::else_if(
		const expr_base						&cond,
		const std::function<void()>		&body,
		const char						*file,
		int32_t							lineno) {
	ModelConstraintScope *true_c = new ModelConstraintScope();
	ModelConstraintIf *if_c = new ModelConstraintIf(
			ctor::inst()->pop_expr(),
			true_c,
			0);
	m_constraint->setFalse(if_c);

	ctor::inst()->push_constraint_scope(true_c);
	body();
	ctor::inst()->pop_constraint_scope();

	return constraint_if_then(if_c);
}

void constraint_if_then::else_then(
		const std::function<void()>		&body,
		const char						*file,
		int32_t							lineno) {
	ModelConstraintScope *else_c = new ModelConstraintScope();
	m_constraint->setFalse(else_c);
	ctor::inst()->push_constraint_scope(else_c);
	body();
	ctor::inst()->pop_constraint_scope();
}

constraint_if_then if_then(
		const expr_base				&cond,
		const std::function<void()>	&body,
		const char					*file,
		int32_t						lineno) {
	return constraint_if_then(cond, body, file, lineno);
}

} /* namespace facade */
} /* namespace vsc */
