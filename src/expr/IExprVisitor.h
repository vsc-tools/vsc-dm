/*
 * IExprVisitor.h
 *
 *  Created on: Jul 3, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_IEXPRVISITOR_H_
#define SRC_EXPR_IEXPRVISITOR_H_

namespace vsc {

class ExprBin;
class IExprVisitor {
public:

	virtual ~IExprVisitor() { }

	virtual void visitExprBin(ExprBin *e) = 0;

};

}


#endif /* SRC_EXPR_IEXPRVISITOR_H_ */
