/*
 * ExprFieldRef.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRFIELDREF_H_
#define SRC_EXPR_EXPRFIELDREF_H_
#include "Expr.h"
#include "Field.h"

namespace vsc {

class ExprFieldRef {
public:
	ExprFieldRef(Field	*field);

	virtual ~ExprFieldRef();

	Field *field() const { return m_field.get(); }

	virtual void accept(IVisitor *v) { v->visitExprFieldRef(this); }

private:
	FieldSP				m_field;
};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRFIELDREF_H_ */
