/*
 * SolveGroup.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_SOLVEGROUP_H_
#define SRC_SOLVER_SOLVEGROUP_H_
#include <memory>

namespace vsc {

/**
 * A SolveGroup captures a set of related fields and
 * constraints
 */
class SolveGroup {
public:
	SolveGroup();

	virtual ~SolveGroup();
};

typedef std::unique_ptr<SolveGroup> SolveGroupUP;

} /* namespace vsc */

#endif /* SRC_SOLVER_SOLVEGROUP_H_ */
