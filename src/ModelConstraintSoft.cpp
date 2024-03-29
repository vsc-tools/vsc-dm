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
 * ModelConstraintSoft.cpp
 *
 *  Created on: Oct 8, 2021
 *      Author: mballance
 */

#include "ModelConstraintSoft.h"

namespace vsc {
namespace dm {

ModelConstraintSoft::ModelConstraintSoft(IModelConstraintExpr *c, int32_t priority) :
	m_constraint(c), m_priority(priority) {

}

ModelConstraintSoft::~ModelConstraintSoft() {
	// TODO Auto-generated destructor stub
}

}
} /* namespace vsc */
