/*
 * IVisitor.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#ifndef SRC_IVISITOR_H_
#define SRC_IVISITOR_H_
#include "expr/IExprVisitor.h"

namespace vsc {

class IVisitor : public virtual IExprVisitor {
public:

	virtual ~IVisitor() { }


};

}



#endif /* SRC_IVISITOR_H_ */
