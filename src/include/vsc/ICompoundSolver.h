/*
 * ICompoundSolver.h
 *
 *  Created on: Mar 23, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelField.h"
#include "vsc/IModelConstraint.h"
#include "vsc/IRandState.h"

namespace vsc {

enum class SolveFlags {
	NoFlags = 0,

	// Randomize fields that are marked used-random (not resolved)
	// Without Randomize set, only SAT/UNSAT is evaluated
	Randomize = (1 << 0),

	// Randomize all decl-rand fields even if they are initially
	// marked 'not UseRandom'
	RandomizeDeclRand = (1 << 1),

	// Consider top fields (and any decl-rand) to be used-random
	// RandomizeTopFields implies Randomize
	RandomizeTopFields = (1 << 2),

	// Produce diagnostics if a failure occurs
	DiagnoseFailures = (1 << 3)
};

static inline SolveFlags operator | (const SolveFlags lhs, const SolveFlags rhs) {
	return static_cast<SolveFlags>(
			static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

static inline SolveFlags operator & (const SolveFlags lhs, const SolveFlags rhs) {
	return static_cast<SolveFlags>(static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

static inline bool operator && (const SolveFlags lhs, const SolveFlags rhs) {
	return (static_cast<uint32_t>(lhs) && static_cast<uint32_t>(rhs));
}

static inline bool operator || (const SolveFlags lhs, const SolveFlags rhs) {
	return (static_cast<uint32_t>(lhs) || static_cast<uint32_t>(rhs));
}

static inline SolveFlags operator ~ (const SolveFlags lhs) {
	return static_cast<SolveFlags>(~static_cast<uint32_t>(lhs));
}


class ICompoundSolver {
public:

	virtual ~ICompoundSolver() { }

	virtual bool solve(
			IRandState								*randstate,
			const std::vector<IModelField *>		&fields,
			const std::vector<IModelConstraint *>	&constraints,
			SolveFlags								flags) = 0;
};
}



