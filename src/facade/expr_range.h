/*
 * expr_range.h
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#pragma once
#include "expr.h"

namespace vsc {
namespace facade {

class expr_range {
public:
	expr_range(
			const expr		&val);

	expr_range(
			const expr		&lower,
			const expr		&upper);

	virtual ~expr_range();

	ModelExprRange *core() const { return m_core; }

private:
	ModelExprRange			*m_core;

};

} /* namespace facade */
} /* namespace vsc */

