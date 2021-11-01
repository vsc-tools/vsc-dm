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
 * constraint.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */

#pragma once
#include <functional>
#include "scope.h"

namespace vsc {
namespace facade {

class rand_obj;

class constraint {
public:
	constraint(const std::function<void()> &body);

	constraint(const std::string &name, const std::function<void()> &body);

	virtual ~constraint();

	const std::string &name() const { return m_name; }

	const std::function<void()> &body() const { return m_body; }

private:
	std::string							m_name;
	std::function<void()>				m_body;

};

} /* namespace facade */
} /* namespace vsc */
