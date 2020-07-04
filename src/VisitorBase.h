/*
 * VisitorBase.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#ifndef SRC_VISITORBASE_H_
#define SRC_VISITORBASE_H_
#include "IVisitor.h"
#include "expr/ExprVisitorBase.h"

namespace vsc {

class VisitorBase : public virtual IVisitor,
	public virtual ExprVisitorBase {
public:
	VisitorBase();
	virtual ~VisitorBase();
};

} /* namespace vsc */

#endif /* SRC_VISITORBASE_H_ */
