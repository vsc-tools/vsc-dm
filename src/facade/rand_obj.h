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
 * rand_obj.h
 *
 *  Created on: Aug 8, 2021
 *      Author: mballance
 */
#pragma once

#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "attr_base.h"
#include "scope.h"

namespace vsc {

class ISolver;
class ISolverFactory;
using ISolverFactoryUP=std::unique_ptr<ISolverFactory>;

namespace facade {

class constraint;

class rand_obj : public attr_base {
public:
	rand_obj(const scope &s);

	virtual ~rand_obj();

	virtual bool randomize();

	virtual bool randomize_with(
			const std::function<void()>	&body);

	void add_constraint(constraint *c);

	virtual void build_constraints();

	void add_field(attr_base *f);

protected:
	ISolverFactory *solver_factory();

private:
	std::vector<attr_base *>					m_fields;
	std::vector<constraint *>					m_constraints;
	std::unordered_map<std::string,int32_t>		m_constraint_name_m;
	std::unordered_set<int32_t>					m_constraint_ov_s;
	ISolverFactoryUP							m_solver_factory;


};

} /* namespace facade */
} /* namespace vsc */

