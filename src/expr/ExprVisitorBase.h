/*
 * ExprVisitorBase.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRVISITORBASE_H_
#define SRC_EXPR_EXPRVISITORBASE_H_
#include "IExprVisitor.h"

namespace vsc {

class ExprVisitorBase : public virtual IExprVisitor {
public:
	ExprVisitorBase();

	virtual ~ExprVisitorBase();
};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRVISITORBASE_H_ */
