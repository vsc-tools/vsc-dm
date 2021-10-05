/*
 * expr.h
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>

namespace vsc {
namespace facade {

class attr_scalar;

class expr {
public:
	expr(const attr_scalar &);

	expr(
			const expr		&lhs,
			const expr		&rhs);

	virtual ~expr();

private:
	const attr_scalar			*m_fieldref;
};

} /* namespace facade */
} /* namespace vsc */

