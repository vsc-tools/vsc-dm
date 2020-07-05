/*
 * RNG.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_RNG_H_
#define SRC_SOLVER_RNG_H_
#include <stdint.h>

namespace vsc {

class RNG {
public:
	RNG(uint64_t seed);

	virtual ~RNG();

	uint64_t next();

private:


};

} /* namespace vsc */

#endif /* SRC_SOLVER_RNG_H_ */
