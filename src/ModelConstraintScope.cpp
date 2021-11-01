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
 * ModelConstraintScope.cpp
 *
 *  Created on: Oct 22, 2021
 *      Author: mballance
 */

#include "ModelConstraintScope.h"

namespace vsc {

ModelConstraintScope::ModelConstraintScope() {
	// TODO Auto-generated constructor stub

}

ModelConstraintScope::~ModelConstraintScope() {
	// TODO Auto-generated destructor stub
}

void ModelConstraintScope::add_constraint(ModelConstraint *c) {
	m_constraints.push_back(ModelConstraintUP(c));
}

} /* namespace vsc */