/*
 * SolveSpec.h
 *
 *  Created on: Oct 7, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <vector>
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
			const std::vector<ModelField *>		&unconstrained);

	virtual ~SolveSpec();

private:
	std::vector<SolveSetUP>			m_solvesets;
	std::vector<ModelField *>		m_unconstrained;
};

} /* namespace vsc */

