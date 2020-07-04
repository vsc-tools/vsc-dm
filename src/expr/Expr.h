/*
 * Expr.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPR_H_
#define SRC_EXPR_EXPR_H_
#include <memory>
#include "IExprVisitor.h"

namespace vsc {

class Expr {
public:
	Expr();

	virtual ~Expr();

	virtual void accept(IExprVisitor *v) = 0;

};

typedef std::shared_ptr<Expr> ExprSP;

} /* namespace vsc */

#endif /* SRC_EXPR_EXPR_H_ */
