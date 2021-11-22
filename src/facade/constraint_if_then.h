/*
 * Copyright 2019-2021 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * if_then.h
 *
 *  Created on: Aug 12, 2021
 *      Author: mballance
 */
#pragma once
#include <functional>
#include "constraint_else_if.h"
#include "constraint_else_then.h"
#include "expr_base.h"
#include "ModelConstraintIf.h"



namespace vsc {
namespace facade {

class constraint_if_then {
	friend constraint_if_then if_then(
		const expr_base					&cond,
		const std::function<void()>	&body,
		const char					*file,
		int32_t						lineno);
public:

	virtual ~constraint_if_then();

	constraint_if_then else_if(
			const expr_base					&cond,
			const std::function<void()> &body,
			const char					*file=0,
			int32_t						lineno=-1);

	void else_then(
			const std::function<void()> &body,
			const char					*file=0,
			int32_t						lineno=-1);

private:
	constraint_if_then(
			const expr_base					&cond,
			const std::function<void()> &body,
			const char					*file=0,
			int32_t						lineno=-1);

	constraint_if_then(
			ModelConstraintIf			*constraint);

private:
	ModelConstraintIf					*m_constraint;

};

/**
 * Method used in user-defined constraints
 */
constraint_if_then if_then(
		const expr_base					&cond,
		const std::function<void()>	&body,
		const char					*file=0,
		int32_t						lineno=-1);

} /* namespace facade */
} /* namespace vsc */

#ifdef UNDEFINED
/**
 * User-facade macro that captures source location
 */
#define if_then(cond, body) \
	if_then(cond, body, __FILE__, __LINE__)

#define else_if(cond, body) \
	else_if(cond, body, __FILE__, __LINE__)

#define else_then(body) \
	else_then(body, __FILE__, __LINE__)
#endif
