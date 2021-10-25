/*
 * SolveSpecBuilder.cpp
 *
 *  Created on: Oct 7, 2021
 *      Author: mballance
 */
#include "Debug.h"
#include "SolveSpecBuilder.h"
#include "glog/logging.h"
#include <iostream>

#undef EN_DEBUG_SOLVE_SPEC_BUILDER
#ifdef EN_DEBUG_SOLVE_SPEC_BUILDER
DEBUG_SCOPE(SolveSpecBuilder)
#define DEBUG_ENTER(fmt, ...) \
		DEBUG_ENTER_BASE(SolveSpecBuilder, fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) \
	DEBUG_LEAVE_BASE(SolveSpecBuilder, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) \
	DEBUG_BASE(SolveSpecBuilder, fmt, ##__VA_ARGS__)
#else
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)
#endif

namespace vsc {

SolveSpecBuilder::SolveSpecBuilder() : m_pass(0), m_active_solveset(0) {
	// TODO Auto-generated constructor stub

}

SolveSpecBuilder::~SolveSpecBuilder() {
	// TODO Auto-generated destructor stub
}

SolveSpec *SolveSpecBuilder::build(
			const std::vector<ModelField *>			&fields,
			const std::vector<ModelConstraint *>	&constraints
			) {
	DEBUG_ENTER("build %d fields %d constraints", fields.size(), constraints.size());

	m_pass = 0;
	for (std::vector<ModelField *>::const_iterator
			it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}

	m_pass = 1;
	for (std::vector<ModelField *>::const_iterator
			it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}
	for (std::vector<ModelConstraint *>::const_iterator
			it=constraints.begin();
			it!=constraints.end(); it++) {
		(*it)->accept(this);
	}

	std::vector<SolveSet *> solvesets;
	for (auto it=m_solveset_l.begin(); it!=m_solveset_l.end(); it++) {
		if (it->get()) {
			solvesets.push_back(it->release());
		}
	}

	std::vector<ModelField *> unconstrained;

	SolveSpec *spec = new SolveSpec(
			solvesets,
			unconstrained);

	DEBUG_LEAVE("build");
	return spec;
}

void SolveSpecBuilder::visitDataTypeInt(DataTypeInt *t) {
	DEBUG_ENTER("visitDataTypeInt");

	if (m_pass == 0) {
		// Save the field
		ModelField *field = m_field_s.back();
		auto it = m_unconstrained_m.find(field);

		if (it == m_unconstrained_m.end()) {
			DEBUG("Add field %s to unconstrained set", field->name().c_str());
			m_unconstrained_m.insert({field, m_unconstrained_l.size()});
			m_unconstrained_l.push_back(field);
		}
	}

	DEBUG_LEAVE("visitDataTypeInt");
}

void SolveSpecBuilder::visitModelConstraintExpr(ModelConstraintExpr *c) {
	DEBUG_ENTER("visitModelConstraintExpr pass=%d", m_pass);
	constraint_enter(c);
	VisitorBase::visitModelConstraintExpr(c);
	constraint_leave(c);
	DEBUG_LEAVE("visitModelConstraintExpr pass=%d", m_pass);
}

void SolveSpecBuilder::visitModelExprFieldRef(ModelExprFieldRef *e) {
	DEBUG_ENTER("visitModelExprFieldRef");
	if (m_pass == 0) {
		// In pass 0, we're collecting fields
		e->field()->accept(this);
	} else {
		// In pass 1, we're evaluating dependencies
		process_fieldref(e->field());
	}
	DEBUG_LEAVE("visitModelExprFieldRef");
}

void SolveSpecBuilder::visitModelField(ModelField *f) {
	DEBUG_ENTER("visitModelField %s", f->name().c_str());
	m_field_s.push_back(f);
	VisitorBase::visitModelField(f);
	m_field_s.pop_back();
	DEBUG_LEAVE("visitModelField %s", f->name().c_str());
}

void SolveSpecBuilder::constraint_enter(ModelConstraint *c) {
	m_constraint_s.push_back(c);
}

void SolveSpecBuilder::constraint_leave(ModelConstraint *c) {
	m_constraint_s.pop_back();

	if (m_pass == 1 && m_constraint_s.size() == 0) {
		if (m_active_solveset) {
			m_active_solveset->add_constraint(c);
		}
	}
}

void SolveSpecBuilder::process_fieldref(ModelField *f) {
	DEBUG_ENTER("process_fieldref %s", f->name().c_str());
	std::unordered_map<ModelField *, SolveSet *>::const_iterator f_it;

	if ((f_it=m_solveset_field_m.find(f)) != m_solveset_field_m.end()) {
		// This field is part of an existing solveset
		DEBUG("In an existing solve set");

		if (!m_active_solveset) {
			// Accept this solveset as the active one
			DEBUG("No active solve set, so take this one");
			m_active_solveset = f_it->second;
		} else if (m_active_solveset != f_it->second) {
			// We have an active solveset which is not the same
			// as the one containing this field. We need to
			// merge the two sets
			DEBUG("Must merge this solve-set with the active one");

			// Relink fields into the new consolidated solveset
			for (std::vector<ModelField *>::const_iterator
					it=f_it->second->all_fields().begin();
					it!=f_it->second->all_fields().end(); it++) {
				// Update the solveset this field is mapped to
				auto it_e = m_solveset_field_m.find(*it);
				it_e->second = m_active_solveset;

				// Add the field to the active solveset
				m_active_solveset->add_field(*it);
			}

			for (std::vector<ModelConstraint *>::const_iterator
					it=f_it->second->constraints().begin();
					it!=f_it->second->constraints().end(); it++) {
				m_active_solveset->add_constraint(*it);
			}

			for (std::vector<ModelConstraintSoft *>::const_iterator
					it=f_it->second->soft_constraints().begin();
					it!=f_it->second->soft_constraints().end(); it++) {
				m_active_solveset->add_soft_constraint(*it);
			}

			// Now, remove the old solveset
			auto solveset_i = m_solveset_m.find(f_it->second);
			m_solveset_l[solveset_i->second] = 0;
		} else {
			DEBUG("Existing solve-set and active are the same");
		}
	} else {
		// The field isn't current managed by a solveset
		DEBUG("Not in an existing solve set (active=%p)", m_active_solveset);

		if (!m_active_solveset) {
			m_active_solveset = new SolveSet();
			m_solveset_m.insert({m_active_solveset, m_solveset_l.size()});
			m_solveset_l.push_back(SolveSetUP(m_active_solveset));
		}

		m_active_solveset->add_field(f);
		m_solveset_field_m.insert({f, m_active_solveset});
	}

	DEBUG_LEAVE("process_fieldref %s", f->name().c_str());
}

} /* namespace vsc */
