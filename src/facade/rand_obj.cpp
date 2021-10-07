/*
 * rand_obj.cpp
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#include "rand_obj.h"
#include "constraint.h"

namespace vsc {
namespace facade {

rand_obj::rand_obj(const scope &s) {
	m_field = new ModelFieldRoot(0, m_name);


	if (m_parent) {
		// Model belongs to the parent scope
		fprintf(stdout, "[%s] parent=%p field=%p\n",
				parent()->fullname().c_str(), parent(), parent()->field());
		parent()->field()->add_field(m_field);
	} else {
		// We own the field since there is no parent scope
		m_field_u = ModelFieldRootUP(m_field);
	}
}

rand_obj::~rand_obj() {
	// TODO Auto-generated destructor stub
}

bool rand_obj::randomize() {
	return false;
}

bool rand_obj::randomize_with(
		const std::function<void()> &body) {

	return false;
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
		m_constraint_en_s.insert(idx);
		m_constraints.push_back(c);
		if (c->name() != "") {
			m_constraint_name_m.insert({c->name(), idx});
		}
	} else {
		// Override
		int32_t ex_idx = it->second;
		int32_t new_idx = m_constraints.size();
		m_constraint_name_m.erase(it);
		m_constraint_name_m.insert({c->name(), new_idx});

		std::unordered_set<int32_t>::const_iterator s_it;
		s_it = m_constraint_en_s.find(ex_idx);
		m_constraint_en_s.erase(s_it);
		m_constraint_en_s.insert(new_idx);
	}
}

void rand_obj::build_constraints() {
	;
}

} /* namespace facade */
} /* namespace vsc */

