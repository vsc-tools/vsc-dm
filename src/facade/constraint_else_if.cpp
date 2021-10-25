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
 * else_if.cpp
 *
 *  Created on: Aug 12, 2021
 *      Author: mballance
 */

#include "constraint_else_if.h"

namespace vsc {
namespace facade {

constraint_else_if::constraint_else_if(
		const expr						&cond,
		const std::function<void()>		&body,
		const char						*file,
		int32_t							line) {
	// TODO Auto-generated constructor stub

}

constraint_else_if::~constraint_else_if() {
	// TODO Auto-generated destructor stub
}

constraint_else_then constraint_else_if::else_then(
		const std::function<void()>		&body,
		const char						*file,
		int32_t							line) {

}

constraint_else_if constraint_else_if::else_if(
		const expr						&cond,
		const std::function<void()>		&body,
		const char						*file,
		int32_t							line) {

}

} /* namespace facade */
} /* namespace vsc */
