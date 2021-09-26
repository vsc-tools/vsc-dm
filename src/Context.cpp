/*
 * Context.cpp
 *
 *  Created on: Sep 8, 2021
 *      Author: mballance
 */

#include "Context.h"

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
	std::unordered_map<int32_t, DataTypeIntUP>::const_iterator it;

	if (is_signed) {
		if ((it=m_sint_type_m.find(width)) != m_sint_type_m.end()) {
			return it->second.get();
		} else if (create) {
			DataTypeInt *t = new DataTypeInt(is_signed, width);

			m_sint_type_m.insert({width, DataTypeIntUP(t)});

			return t;
		}
	} else {
		if ((it=m_uint_type_m.find(width)) != m_uint_type_m.end()) {
			return it->second.get();
		} else if (create) {
			DataTypeInt *t = new DataTypeInt(is_signed, width);

			m_uint_type_m.insert({width, DataTypeIntUP(t)});

			return t;
		}
	}

	return 0;
}

} /* namespace vsc */
