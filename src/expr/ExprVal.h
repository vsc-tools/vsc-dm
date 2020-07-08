/*
 * ExprVal.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRVAL_H_
#define SRC_EXPR_EXPRVAL_H_
#include <memory>

namespace vsc {

enum ExprValType {
	ValType_Numeric,
};

class ExprVal {
public:
	ExprVal(ExprValType type);

	virtual ~ExprVal();

	ExprValType type() const { return m_type; }

private:
	ExprValType			m_type;

};

typedef std::shared_ptr<ExprVal> ExprValSP;

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRVAL_H_ */
