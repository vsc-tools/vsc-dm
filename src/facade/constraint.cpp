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
 * constraint.cpp
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#include "constraint.h"
#include "rand_obj.h"
#include "ctor.h"
#include "Debug.h"
#include "ModelConstraintBlock.h"
#include "ModelField.h"

#undef EN_DEBUG_CONSTRAINT

#ifdef EN_DEBUG_CONSTRAINT
#define DEBUG_ENTER(fmt, ...) \
	DEBUG_ENTER_BASE(constraint, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) \
	DEBUG_LEAVE_BASE(constraint, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) \
	DEBUG_BASE(constraint, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif


namespace vsc {
namespace facade {

/*
constraint::constraint(
		const std::function<void ()>	&body) : m_body(body) {
	fprintf(stdout, "--> constraint\n");
	fflush(stdout);
	rand_obj *scope = ctor::inst()->scope();
	scope->add_constraint(this);
	fprintf(stdout, "<-- constraint\n");
	fflush(stdout);
}
 */

constraint::constraint(
		const scope 					&name,
		const std::function<void ()>	&body) :
				obj(ObjType_Constraint), m_body(body) {

}

constraint::~constraint() {
	// TODO Auto-generated destructor stub
}

void constraint::build() {
	DEBUG_ENTER("build(phase=%d)", ctor::inst()->build_phase());
	if (ctor::inst()->build_phase() == 1) {
		ModelConstraintBlock *c = new ModelConstraintBlock(name());
		ctor::inst()->push_constraint_scope(c);

		m_body();

		ctor::inst()->pop_constraint_scope();
		DEBUG("Adding constraint body (%d statements)", c->constraints().size());
		ctor::inst()->build_field()->add_constraint(c);
	}
	DEBUG_LEAVE("build(phase=%d)", ctor::inst()->build_phase());
}

} /* namespace facade */
} /* namespace vsc */
