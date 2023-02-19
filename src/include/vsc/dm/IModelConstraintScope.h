/*
 * IModelConstraintScope.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 * 
 * Copyright 2019-2023 Matthew Ballance and contributors
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
 */

#pragma once
#include <vector>
#include "vsc/dm/IModelConstraint.h"

namespace vsc {
namespace dm {

class IModelConstraintScope;
using IModelConstraintScopeUP=UP<IModelConstraintScope>;
class IModelConstraintScope : public virtual IModelConstraint {
public:
	virtual ~IModelConstraintScope() { }

	virtual const std::vector<IModelConstraintUP> &getConstraints() const = 0;

	virtual void addConstraint(
        IModelConstraint    *c,
        bool                owned=true) = 0;
};

}
}
