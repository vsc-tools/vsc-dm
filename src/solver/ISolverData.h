/*
 * ISolverData.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_SOLVER_ISOLVERDATA_H_
#define SRC_SOLVER_ISOLVERDATA_H_
#include <memory>

namespace vsc {

// Opaque representation of per-field solver data
class ISolverData {
public:

	virtual ~ISolverData() { }

};

typedef std::unique_ptr<ISolverData> ISolverDataUP;

}



#endif /* SRC_SOLVER_ISOLVERDATA_H_ */
