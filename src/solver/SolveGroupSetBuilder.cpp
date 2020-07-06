/*
 * SolveGroupSetBuilder.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: ballance
 */

#include "SolveGroupSetBuilder.h"

namespace vsc {

SolveGroupSetBuilder::SolveGroupSetBuilder() {
	// TODO Auto-generated constructor stub

}

SolveGroupSetBuilder::~SolveGroupSetBuilder() {
	// TODO Auto-generated destructor stub
}

SolveGroupSet *SolveGroupSetBuilder::build(
		const std::vector<FieldSP>				&fields,
		const std::vector<ConstraintBlockSP>	&constraints) {

	// First, collect all fields
	m_pass = 0;
	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}

	// Now, build up the solve groups
	m_pass = 1;
	m_used_rand = true;
	for (std::vector<FieldSP>::const_iterator it=fields.begin();
			it!=fields.end(); it++) {
		(*it)->accept(this);
	}
	for (std::vector<ConstraintBlockSP>::const_iterator it=constraints.begin();
			it!=constraints.end(); it++) {
		(*it)->accept(this);
	}

	SolveGroupSet *ret = new SolveGroupSet();

	for (std::set<SolveGroup *>::const_iterator it=m_solvegroup_s.begin();
			it!=m_solvegroup_s.end(); it++) {
		// Transfers ownership to SolveGroupSet
		ret->addSolveGroup(*it);
	}

	for (std::set<FieldSP>::const_iterator it=m_field_s.begin();
			it!=m_field_s.end(); it++) {
		ret->addUnconstrained(*it);
	}

	return ret;
}



} /* namespace vsc */
