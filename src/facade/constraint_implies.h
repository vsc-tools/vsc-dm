/*
 * constraint_implies.h
 *
 *  Created on: Nov 2, 2021
 *      Author: mballance
 */

#pragma once
#include "expr.h"
#include <functional>

namespace vsc {
namespace facade {

class constraint_implies {
public:
	constraint_implies(
			const expr					&cond,
			const std::function<void()>	&body,
			const char					*file,
			int32_t						lineno);

	virtual ~constraint_implies();
};

} /* namespace facade */
} /* namespace vsc */

#define implies(expr, body) \
	constraint_implies(expr, body, __FILE__, __LINE__)
