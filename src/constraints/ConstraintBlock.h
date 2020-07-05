/*
 * ConstraintBlock.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_CONSTRAINTS_CONSTRAINTBLOCK_H_
#define SRC_CONSTRAINTS_CONSTRAINTBLOCK_H_
#include <memory>

namespace vsc {

class ConstraintBlock {
public:
	ConstraintBlock();
	virtual ~ConstraintBlock();
};

typedef std::shared_ptr<ConstraintBlock> ConstraintBlockSP;

} /* namespace vsc */

#endif /* SRC_CONSTRAINTS_CONSTRAINTBLOCK_H_ */
