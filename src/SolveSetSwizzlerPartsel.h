/*
 * SolveSetSwizzlerPartsel.h
 *
 *  Created on: Oct 24, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/ISolver.h"
#include "vsc/IRandState.h"
#include "SolveSet.h"

namespace vsc {

class SolveSetSwizzlerPartsel {
public:
	SolveSetSwizzlerPartsel(IRandState *rand_state);

	virtual ~SolveSetSwizzlerPartsel();

	void swizzle(
			ISolver		*solver,
			SolveSet	*sset);

private:
	void swizzle_field_l(
			const std::vector<IModelField *>	&fields);

	void swizzle_field(
			IModelField						*f,
			std::vector<IModelConstraintUP>	&constraints);

	void create_rand_domain_constraint(
			IModelField						*f,
			std::vector<IModelConstraintUP>	&constraints);

private:
	IRandState				*m_randstate;
	ISolver					*m_solver;
	SolveSet				*m_sset;

};

} /* namespace vsc */

