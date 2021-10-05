/*
 * if_then.h
 *
 *  Created on: Aug 12, 2021
 *      Author: mballance
 */
#pragma once
#include <functional>
#include "expr.h"
#include "constraint_else_if.h"
#include "constraint_else_then.h"

namespace vsc {
namespace facade {

class constraint_if_then {
	friend constraint_if_then if_then(
		const expr					&cond,
		const std::function<void()>	&body,
		const char					*file,
		int32_t						lineno);
public:

	virtual ~constraint_if_then();

	constraint_else_if else_if(
			const expr					&cond,
			const std::function<void()> &body,
			const char					*file=0,
			int32_t						lineno=-1);

	constraint_else_then else_then(
			const std::function<void()> &body,
			const char					*file=0,
			int32_t						lineno=-1);

private:
	constraint_if_then(
			const expr					&cond,
			const std::function<void()> &body,
			const char					*file=0,
			int32_t						lineno=-1);

};

/**
 * Method used in user-defined constraints
 */
constraint_if_then (if_then)(
		const expr					&cond,
		const std::function<void()>	&body,
		const char					*file=0,
		int32_t						lineno=-1);

} /* namespace facade */
} /* namespace vsc */

