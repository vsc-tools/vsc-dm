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
#include "vsc/IModelConstraint.h"
#include "vsc/IModelConstraintSoft.h"
#include "vsc/IModelField.h"
#include "vsc/IModelFieldVec.h"

namespace vsc {

enum class SolveSetFlag {
	NoFlags = 0,
	HaveForeach = (1 << 0)
};

static inline SolveSetFlag operator | (const SolveSetFlag lhs, const SolveSetFlag rhs) {
	return static_cast<SolveSetFlag>(
			static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

static inline SolveSetFlag operator |= (SolveSetFlag &lhs, const SolveSetFlag rhs) {
	lhs = static_cast<SolveSetFlag>(
			static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
	return lhs;
}

static inline SolveSetFlag operator & (const SolveSetFlag lhs, const SolveSetFlag rhs) {
	return static_cast<SolveSetFlag>(
			static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

static inline SolveSetFlag operator ~ (const SolveSetFlag lhs) {
	return static_cast<SolveSetFlag>(~static_cast<uint32_t>(lhs));
}

class SolveSet;
using SolveSetUP = std::unique_ptr<SolveSet>;

class SolveSet {
public:
	SolveSet();

	virtual ~SolveSet();

	void add_field(IModelField *f);

	void add_constraint(IModelConstraint *c);

	void add_soft_constraint(IModelConstraintSoft *c);

	const std::vector<IModelField *> &all_fields() const {
		return m_all_fields;
	}

	const std::vector<IModelField *> &rand_fields() const {
		return m_rand_fields;
	}

	const std::vector<IModelFieldVec *> &constrained_sz_vec() const {
		return m_constrained_sz_vec;
	}

	const std::vector<IModelConstraint *> &constraints() const {
		return m_constraints;
	}

	const std::vector<IModelConstraintSoft *> &soft_constraints() const {
		return m_soft_constraints;
	}

	SolveSetFlag getFlags() const { return m_flags; }

	void setFlags(SolveSetFlag flags) { m_flags |= flags; }

	bool hasFlags(SolveSetFlag flags) { return (m_flags & flags) == flags; }

	/**
	 * Merge data from the `src` set into this one
	 */
	void merge(SolveSet *src);

private:
	std::unordered_set<IModelField *>			m_field_s;
	std::vector<IModelField *>					m_all_fields;
	std::vector<IModelField *>					m_rand_fields;
	std::vector<IModelFieldVec *>				m_constrained_sz_vec;
	std::unordered_set<IModelConstraint *>		m_constraint_s;
	std::vector<IModelConstraint *>				m_constraints;

	std::unordered_set<IModelConstraintSoft *>	m_soft_constraint_s;
	std::vector<IModelConstraintSoft *>			m_soft_constraints;
	SolveSetFlag								m_flags;

};

} /* namespace vsc */

