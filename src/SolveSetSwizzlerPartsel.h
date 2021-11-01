/*
 * SolveSetSwizzlerPartsel.h
 *
 *  Created on: Oct 24, 2021
 *      Author: mballance
 */

#pragma once
#include "ISolver.h"
#include "RandState.h"
#include "SolveSet.h"

namespace vsc {

class SolveSetSwizzlerPartsel {
public:
	SolveSetSwizzlerPartsel(RandState *rand_state);

	virtual ~SolveSetSwizzlerPartsel();

	void swizzle(
			ISolver		*solver,
			SolveSet	*sset);

private:
	void swizzle_field_l(
			const std::vector<ModelField *>	&fields);

	void swizzle_field(
			ModelField 						*f,
			std::vector<ModelConstraintUP>	&constraints);

	void create_rand_domain_constraint(
			ModelField						*f,
			std::vector<ModelConstraintUP>	&constraints);

private:
	RandState				*m_randstate;
	ISolver					*m_solver;
	SolveSet				*m_sset;

};

} /* namespace vsc */

