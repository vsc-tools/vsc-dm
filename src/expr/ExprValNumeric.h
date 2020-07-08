/*
 * ExprValNumeric.h
 *
 *  Created on: Jul 7, 2020
 *      Author: ballance
 */

#ifndef SRC_EXPR_EXPRVALNUMERIC_H_
#define SRC_EXPR_EXPRVALNUMERIC_H_
#include "expr/ExprVal.h"

namespace vsc {

class ExprValNumeric : public ExprVal {
public:
	ExprValNumeric();

	virtual ~ExprValNumeric();

	virtual uint64_t val_u() const {
		return m_val;
	}

	virtual int64_t val_s() const {
		return static_cast<int64_t>(m_val);
	}

private:
	uint64_t		m_val;
};

typedef std::shared_ptr<ExprValNumeric> ExprValNumericSP;

} /* namespace vsc */

#endif /* SRC_EXPR_EXPRVALNUMERIC_H_ */
