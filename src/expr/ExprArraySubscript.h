/*
 * ExprArraySubscript.h
 *
 *  Created on: Jul 4, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRARRAYSUBSCRIPT_H_
#define SRC_EXPR_EXPRARRAYSUBSCRIPT_H_
#include "../datamodel/FieldList.h"
#include "Expr.h"

namespace vsc {

class ExprArraySubscript : public Expr {
public:
	ExprArraySubscript(
			FieldList		*lhs,
			Expr			*rhs);

	virtual ~ExprArraySubscript();

private:
	FieldArraySP			m_lhs;
	ExprSP					m_rhs;
};

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRARRAYSUBSCRIPT_H_ */
