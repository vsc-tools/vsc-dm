/*
 * SolveSet.cpp
 *
 *  Created on: Oct 7, 2021
 *      Author: mballance
 */

#include "SolveSet.h"

namespace vsc {

SolveSet::SolveSet() {
	// TODO Auto-generated constructor stub

}

SolveSet::~SolveSet() {
	// TODO Auto-generated destructor stub
}

void SolveSet::add_field(ModelField *f) {
	if (m_field_s.find(f) == m_field_s.end()) {
		m_all_fields.push_back(f);
		// TODO: if rand...
		m_field_s.insert(f);
	}
}

void SolveSet::add_constraint(ModelConstraint *c) {
	if (m_constraint_s.find(c) == m_constraint_s.end()) {
		m_constraints.push_back(c);
		m_constraint_s.insert(c);
	}
}

void SolveSet::add_soft_constraint(ModelConstraintSoft *c) {
	if (m_soft_constraint_s.find(c) == m_soft_constraint_s.end()) {
		m_soft_constraints.push_back(c);
		m_soft_constraint_s.insert(c);
	}
}

} /* namespace vsc */
