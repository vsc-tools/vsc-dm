/*
 * ExprFieldRef.h
 *
 *  Created on: Jul 5, 2020
 *      Author: ballance
 */

#pragma once
#include "Expr.h"
#include "Field.h"

namespace vsc {

class ExprFieldRef : public Expr {
public:
	ExprFieldRef(Field	*field);

	virtual ~ExprFieldRef();

	Field *field() const { return m_field; }

	virtual void accept(IVisitor *v) { v->visitExprFieldRef(this); }

private:
	Field				*m_field;
};

} /* namespace vsc */

