/*
 * SolveSet.h
 *
 *  Created on: Oct 7, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <unordered_set>
#include <vector>
#include "ModelConstraint.h"
#include "ModelConstraintSoft.h"
#include "ModelField.h"

namespace vsc {

class SolveSet;
using SolveSetUP = std::unique_ptr<SolveSet>;

class SolveSet {
public:
	SolveSet();

	virtual ~SolveSet();

	void add_field(ModelField *f);

	void add_constraint(ModelConstraint *c);

	void add_soft_constraint(ModelConstraintSoft *c);

	const std::vector<ModelField *> &all_fields() const {
		return m_all_fields;
	}

	const std::vector<ModelField *> &rand_fields() const {
		return m_rand_fields;
	}

	const std::vector<ModelConstraint *> &constraints() const {
		return m_constraints;
	}

	const std::vector<ModelConstraintSoft *> &soft_constraints() const {
		return m_soft_constraints;
	}

	/**
	 * Merge data from the `src` set into this one
	 */
	void merge(SolveSet *src);

private:
	std::unordered_set<ModelField *>			m_field_s;
	std::vector<ModelField *>					m_all_fields;
	std::vector<ModelField *>					m_rand_fields;
	std::vector<ModelFieldVec *>				m_constrained_sz_vec;
	std::unordered_set<ModelConstraint *>		m_constraint_s;
	std::vector<ModelConstraint *>				m_constraints;

	std::unordered_set<ModelConstraintSoft *>	m_soft_constraint_s;
	std::vector<ModelConstraintSoft *>			m_soft_constraints;

};

} /* namespace vsc */

