/*
 * ITypeConstraintBlock.h
 *
 *  Created on: Apr 8, 2022
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
#include <string>
#include <vector>
#include "vsc/dm/ITypeConstraintScope.h"


namespace vsc {
namespace dm {
class ITypeConstraintBlock : public ITypeConstraintScope {
public:

	virtual ~ITypeConstraintBlock() { }

	virtual const std::string &name() const = 0;

};

}
}
