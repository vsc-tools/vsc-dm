/*
 * SolveSetSwizzlerPartsel.cpp
 *
 *  Created on: Oct 24, 2021
 *      Author: mballance
 */

#include "SolveSetSwizzlerPartsel.h"

namespace vsc {

SolveSetSwizzlerPartsel::SolveSetSwizzlerPartsel(RNG &rng) : m_rng(rng) {
	m_solver = 0;
	m_sset = 0;
}

SolveSetSwizzlerPartsel::~SolveSetSwizzlerPartsel() {
	// TODO Auto-generated destructor stub
}

void SolveSetSwizzlerPartsel::swizzle(
			ISolver		*solver,
			SolveSet	*sset) {
	m_solver = solver;
	m_sset = sset;

	// TODO: handle solve order
	swizzle_field_l(sset->rand_fields());

	;
}

void SolveSetSwizzlerPartsel::swizzle_field_l(
		const std::vector<ModelField *>		&fields) {

	uint32_t max_swizzle = 4;
	// Create a copy for random selection
	std::vector<ModelField *> fields_c(fields.begin(), fields.end());
	std::vector<ModelConstraintUP> constraints;

	for (uint32_t i=0; i<max_swizzle && fields_c.size(); i++) {
		uint32_t target_idx = m_rng.randint_u(0, fields_c.size()-1);
		ModelField *field = fields.at(target_idx);
		fields_c.erase(fields_c.begin()+target_idx);
		swizzle_field(field, constraints);
	}

	// Build out the solver representation
	for (auto c_it=constraints.begin(); c_it!=constraints.end(); c_it++) {
		m_solver->initConstraint(c_it->get());
	}

	// Now, apply as many as possible
}

void SolveSetSwizzlerPartsel::swizzle_field(
		ModelField 							*f,
		std::vector<ModelConstraintUP>		&constraints) {

	// TODO: handle distribution
	if (false /* Have distribution */) {
	} else if (false /* Have multi-interval domain */) {
	} else {
		create_rand_domain_constraint(f, constraints);
	}
}

void SolveSetSwizzlerPartsel::create_rand_domain_constraint(
			ModelField						*f,
			std::vector<ModelConstraintUP>	&constraints) {
	// TODO: Should be able to incorporate min/max information.
	// Specifically, there is a width inside min/max
	// TODO: should probably do this with 'val' to ensure we
	// can handle wide variables
	uint32_t width = 8;
	uint32_t bit_pattern = m_rng.randint_u(0, (1 << width)-1);
	uint32_t max_intervals = 6;

	if (width > max_intervals) {
		// Partition into 'max_intervals' ranges
	} else {
		// Single bits
	}
}

} /* namespace vsc */
