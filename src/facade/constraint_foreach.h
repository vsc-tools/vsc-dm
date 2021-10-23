/*
 * constraint_foreach.h
 *
 *  Created on: Oct 17, 2021
 *      Author: mballance
 */

#pragma once
#include <functional>
#include "expr.h"

namespace vsc {
namespace facade {

class constraint_foreach {
public:
	constraint_foreach(
			const expr		&target,
			const std::function<void(uint32_t i)>	&body,
			const char								*file,
			int32_t									lineno);

	virtual ~constraint_foreach();
};

void (foreach)(
		const expr								&target,
		const std::function<void(uint32_t i)>	&body,
		const char								*file=0,
		int32_t									lineno=-1
		);

} /* namespace facade */
} /* namespace vsc */

