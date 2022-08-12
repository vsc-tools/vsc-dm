/*
 * SolveSpec.h
 *
 *  Created on: Oct 7, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <vector>
#include "vsc/IModelFieldVec.h"
#include "ModelField.h"
#include "SolveSet.h"

namespace vsc {

class SolveSpec;
using SolveSpecUP = std::unique_ptr<SolveSpec>;

/**
 * Contains data specifying the solve problem
 * - Related fields
 * - Unconstrained fields
 * - ...
 */
class SolveSpec {
public:
	SolveSpec(
			const std::vector<SolveSet *>		&solvesets,
			const std::vector<IModelField *>	&unconstrained,
			const std::vector<IModelFieldVec *>	&unconstrained_sz_vec);

	virtual ~SolveSpec();

	const std::vector<SolveSetUP> &solvesets() const {
		return m_solvesets;
	}

	const std::vector<IModelField *> &unconstrained() const {
		return m_unconstrained;
	}

	const std::vector<IModelFieldVec *> &unconstrained_sz_vec() const {
		return m_unconstrained_sz_vec;
	}

private:
	std::vector<SolveSetUP>			m_solvesets;
	std::vector<IModelField *>		m_unconstrained;
	std::vector<IModelFieldVec *>	m_unconstrained_sz_vec;
};

} /* namespace vsc */

