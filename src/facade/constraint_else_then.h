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

