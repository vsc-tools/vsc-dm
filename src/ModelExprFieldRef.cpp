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
 * ModelExprFieldRef.cpp
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#include "ModelExprFieldRef.h"

namespace vsc {
namespace dm {

ModelExprFieldRef::ModelExprFieldRef(IModelField *field) : m_field(field) {

}

ModelExprFieldRef::~ModelExprFieldRef() {
	// TODO Auto-generated destructor stub
}

void ModelExprFieldRef::eval(IModelVal *dst) {
    /*
	dst = m_field->val();
	fprintf(stdout, "ModelExprFieldRef::eval %lld %d (%lld %d)\n",
			dst->val_u(), dst->bits(),
			m_field->val()->val_u(), m_field->val()->bits());
     */
}

}
} /* namespace vsc */
