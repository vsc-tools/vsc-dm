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
 * constraint_foreach.cpp
 *
 *  Created on: Oct 17, 2021
 *      Author: mballance
 */

#include "constraint_foreach.h"

namespace vsc {
namespace facade {

constraint_foreach::constraint_foreach(
		const expr_base								&target,
		const std::function<void(uint32_t i)>	&body,
		const char								*file,
		int32_t									lineno) {
	// TODO Auto-generated constructor stub

}

constraint_foreach::~constraint_foreach() {
	// TODO Auto-generated destructor stub
}

} /* namespace facade */
} /* namespace vsc */
