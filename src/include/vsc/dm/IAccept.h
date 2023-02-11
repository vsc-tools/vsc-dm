/*
 * IAccept.h
 *
 *  Created on: Aug 2, 2020
 *      Author: ballance
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
#include <memory>
#include "vsc/dm/impl/UP.h"
#include "vsc/dm/IVisitor.h"

namespace vsc {
namespace dm {

class IAccept;
using IAcceptUP=UP<IAccept>;
class IAccept {
public:
	virtual ~IAccept() { }

	virtual void accept(IVisitor *v) = 0;

};

}
}
