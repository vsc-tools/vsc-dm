/*
 * constraint_else_then.h
 *
 *  Created on: Aug 12, 2021
 *      Author: mballance
 */

#pragma once
#include <functional>

namespace vsc {
namespace facade {

class constraint_else_then {
	friend class constraint_if_then;
	friend class constraint_else_then;
public:

	virtual ~constraint_else_then();

private:
	constraint_else_then(
			const std::function<void()>	&body,
			const char					*file,
			int32_t						lineno);

};

} /* namespace facade */
} /* namespace vsc */

