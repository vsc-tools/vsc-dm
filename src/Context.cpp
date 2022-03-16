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
 * Context.cpp
 *
 *  Created on: Sep 8, 2021
 *      Author: mballance
 */

#include "Context.h"
#include "ModelFieldRoot.h"
#include "Randomizer.h"
#include "RandState.h"

namespace vsc {

Context::Context() {
	// TODO Auto-generated constructor stub

}

Context::~Context() {
	// TODO Auto-generated destructor stub
}

DataTypeStruct *Context::findStructType(const std::string &name) {
	std::unordered_map<std::string, DataTypeStructUP>::const_iterator it;

	if ((it=m_struct_type_m.find(name)) != m_struct_type_m.end()) {
		return it->second.get();
	} else {
		return 0;
	}
}

void Context::addStructType(DataTypeStruct *t) {
	m_struct_type_m.insert({t->name(), DataTypeStructUP(t)});
}

DataTypeInt *Context::findIntType(
		bool				is_signed,
		int32_t				width,
		bool				create) {
	std::unordered_map<int32_t, DataTypeInt *>::const_iterator it;

	if (is_signed) {
		if ((it=m_sint_type_m.find(width)) != m_sint_type_m.end()) {
			return it->second;
		} else if (create) {
			DataTypeInt *t = new DataTypeInt(is_signed, width);

			m_sint_type_m.insert({width, t});
			m_sint_type_l.push_back(DataTypeIntUP(t));

			return t;
		}
	} else {
		if ((it=m_uint_type_m.find(width)) != m_uint_type_m.end()) {
			return it->second;
		} else if (create) {
			DataTypeInt *t = new DataTypeInt(is_signed, width);

			m_uint_type_m.insert({width, t});
			m_uint_type_l.push_back(DataTypeIntUP(t));

			return t;
		}
	}

	return 0;
}

IDataTypeInt *Context::mkDataTypeInt(
			bool			is_signed,
			int32_t			width) {
	DataTypeInt *ret = 0;

	if (is_signed) {
		auto it = m_sint_type_m.find(width);
		if (it == m_sint_type_m.end()) {
			// New type
			ret = new DataTypeInt(is_signed, width);
			m_sint_type_m.insert({width, ret});
			m_sint_type_l.push_back(DataTypeIntUP(ret));
		} else {
			ret = it->second;
		}
	} else {
		auto it = m_uint_type_m.find(width);
		if (it == m_uint_type_m.end()) {
			// New type
			ret = new DataTypeInt(is_signed, width);
			m_uint_type_m.insert({width, ret});
			m_uint_type_l.push_back(DataTypeIntUP(ret));
		} else {
			ret = it->second;
		}
	}
	return ret;
}

IModelField *Context::mkModelFieldRoot(
			IDataType 			*type,
			const std::string	&name) {
	return new ModelFieldRoot(type, name);
}

IRandomizer *Context::mkRandomizer(
			ISolverFactory		*solver_factory,
			IRandState			*randstate) {
	return new Randomizer(solver_factory, randstate);
}

IRandState *Context::mkRandState(uint32_t seed) {
	return new RandState(seed);
}

} /* namespace vsc */
