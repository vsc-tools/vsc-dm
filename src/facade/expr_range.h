/*
 * expr_range.h
 *
 *  Created on: Nov 5, 2021
 *      Author: mballance
 */

#pragma once
#include "expr_base.h"

namespace vsc {
namespace facade {

class expr_range {
public:

	expr_base				lower;
	expr_base				upper;

	/*
public:
	expr_range(
			const expr_base		&val);

	expr_range(
			const expr_base		&lower,
			const expr_base		&upper);

	virtual ~expr_range();

	ModelExprRange *core() const { return m_core; }

private:
	ModelExprRange			*m_core;
	 */

};

} /* namespace facade */
} /* namespace vsc */

