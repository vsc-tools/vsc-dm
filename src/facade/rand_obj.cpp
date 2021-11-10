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
 * rand_obj.cpp
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#include "rand_obj.h"
#include "constraint.h"
#include "ctor.h"
#include "Debug.h"
#include "ModelConstraintScope.h"
#include "Randomizer.h"
#include "SetFieldUsedRandVisitor.h"
#include "SolverFactoryDefault.h"

#undef EN_DEBUG_RAND_OBJ

#ifdef EN_DEBUG_RAND_OBJ
#define DEBUG_ENTER(fmt, ...) \
	DEBUG_ENTER_BASE(rand_obj, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) \
	DEBUG_LEAVE_BASE(rand_obj, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) \
	DEBUG_BASE(rand_obj, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {
namespace facade {

rand_obj::rand_obj(const scope &s) {
	m_field = new ModelFieldRoot(0, m_name);


	if (m_parent) {
		// Model belongs to the parent scope
		static_cast<rand_obj *>(parent())->add_field(this);
	} else {
		// We own the field since there is no parent scope
		m_field_u = ModelFieldUP(m_field);
	}
}

rand_obj::~rand_obj() {
	// TODO Auto-generated destructor stub
}

bool rand_obj::randomize() {
	if (!m_randstate) {
		m_randstate = RandStateUP(ctor::inst()->mk_randstate());
	}
	Randomizer randomizer(
			solver_factory(),
			m_randstate.get());
	std::vector<ModelField *> 		fields;
	std::vector<ModelConstraint *> 	constraints;
	bool diagnose_failures = false;

	SetFieldUsedRandVisitor().set(field());
	fields.push_back(field());

	return randomizer.randomize(
			fields,
			constraints,
			diagnose_failures);
}

bool rand_obj::randomize_with(
		const std::function<void()> &body) {
	if (!m_randstate) {
		m_randstate = RandStateUP(ctor::inst()->mk_randstate());
	}
	Randomizer randomizer(
			solver_factory(),
			m_randstate.get());
	std::vector<ModelField *> 		fields;
	std::vector<ModelConstraint *> 	constraints;
	bool diagnose_failures = false;

	// Collect 'with' constraints
	ModelConstraintScope with_c;
	ctor::inst()->push_constraint_scope(&with_c);
	body();
	ctor::inst()->pop_constraint_scope();

	SetFieldUsedRandVisitor().set(field());
	fields.push_back(field());
	constraints.push_back(&with_c);

	return randomizer.randomize(
			fields,
			constraints,
			diagnose_failures);
}

// Track constraints such that inheritance can be
// implemented.
// - The 'constraints' list holds all constraints
// - The 'constraint_name_m' holds a mapping from constraint-block
//   name to constraint index
// - The 'constraint_en_s' holds the set of enabled indexes
//
// Classes are built inside-out, so base constraints are built first.
// If we encounter a constraint with a non-empty name that already
// exists in the map, then it overrides the previously-specified entry:
// - The map target (constraint index) is updated
// - The old index is removed from the 'enabled' list
// - The new index is added to the 'enabled' list
void rand_obj::add_constraint(constraint *c) {
	std::unordered_map<std::string,int32_t>::const_iterator it;

	it = m_constraint_name_m.find(c->name());

	if (c->name() == "" || (it == m_constraint_name_m.end())) {
		// Anonymous constraint or first entry
		int32_t idx = m_constraints.size();
		m_constraints.push_back(c);
		if (c->name() != "") {
			m_constraint_name_m.insert({c->name(), idx});
		}
	} else {
		// Override
		int32_t ex_idx = it->second;
		int32_t new_idx = m_constraints.size();
		m_constraints.push_back(c);
		m_constraint_name_m.erase(it);
		m_constraint_name_m.insert({c->name(), new_idx});

		std::unordered_set<int32_t>::const_iterator s_it;
		// Mark the existing index as an overridden one
		m_constraint_ov_s.insert(ex_idx);
	}
}

void rand_obj::build_constraints() {
	// First process sub-scopes
	DEBUG_ENTER("build_constraints: %s n_constraints=%d n_constraint_ov=%d",
			fullname().c_str(),
			m_constraints.size(),
			m_constraint_ov_s.size());
	for (auto f : m_fields) {
		f->build_constraints();
	}

	for (uint32_t i=0; i<m_constraints.size(); i++) {
		if (m_constraint_ov_s.find(i) == m_constraint_ov_s.end()) {
			ctor::inst()->push_constraint_scope(new ModelConstraintScope());
			ctor::inst()->push_expr_mode();
			m_constraints.at(i)->body()();
			ctor::inst()->pop_expr_mode();
			ModelConstraintScope *c = ctor::inst()->pop_constraint_scope();
			field()->add_constraint(c);
		}
	}
	DEBUG_LEAVE("build_constraints: %s n_constraints=%d n_constraint_ov=%d",
			fullname().c_str(),
			m_constraints.size(),
			m_constraint_ov_s.size());
}

void rand_obj::add_field(attr_base *f) {
	f->idx(m_fields.size());
	m_fields.push_back(f);

	m_field->add_field(f->field());
}

ISolverFactory *rand_obj::solver_factory() {
	if (!m_solver_factory) {
		// Initialize with the default factory
		m_solver_factory = ISolverFactoryUP(new SolverFactoryDefault());
	}
	return m_solver_factory.get();
}

} /* namespace facade */
} /* namespace vsc */

