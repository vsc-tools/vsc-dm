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
 * scope.h
 *
 *  Created on: Aug 9, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include <typeinfo>
#include "scope_base.h"

namespace vsc {
namespace facade {

class scope : public scope_base {
public:

	scope(const char *name) : scope_base(name) { }

	scope(const std::string &name) : scope_base(name) { }

	template <class T> scope(T *s) : scope_base(s, typeid(T)) { };

	template <class T> scope(
			T 					*s,
			const std::string	&name) : scope_base(s, typeid(T), name) { };

};

}
}
