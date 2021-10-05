/*
 * else_if.h
 *
 *  Created on: Aug 12, 2021
 *      Author: mballance
 */

#pragma once
#include <functional>
#include "constraint_else_then.h"
#include "expr.h"

namespace vsc {
namespace facade {

class constraint_else_if {
public:

	virtual ~constraint_else_if();

	constraint_else_if else_if(
			const expr						&cond,
			const std::function<void()>		&body,
			const char						*file=0,
			int32_t							line=-1);

	constraint_else_then else_then(
			const std::function<void()>		&body,
			const char						*file=0,
			int32_t							line=-1);

private:
	constraint_else_if(
			const expr						&cond,
			const std::function<void()>		&body,
			const char						*file,
			int32_t							line);

};

} /* namespace facade */
} /* namespace vsc */

