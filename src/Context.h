/*
 * Context.h
 *
 *  Created on: Sep 8, 2021
 *      Author: mballance
 */

#pragma once
#include <unordered_map>
#include "DataTypeInt.h"
#include "DataTypeStruct.h"

namespace vsc {

class Context {
public:
	Context();

	virtual ~Context();

	DataTypeStruct *findStructType(const std::string &name);

	void addStructType(DataTypeStruct *t);

	DataTypeInt *findIntType(
			bool			is_signed,
			int32_t			width,
			bool			create=true);

	void addIntType(DataTypeInt		*t);

private:

	std::unordered_map<std::string,DataTypeStructUP>		m_struct_type_m;
	std::vector<DataTypeStruct *>							m_struct_type_l;

	std::unordered_map<int32_t, DataTypeIntUP>				m_uint_type_m;
	std::vector<DataTypeInt *>								m_uint_type_l;

	std::unordered_map<int32_t, DataTypeIntUP>				m_sint_type_m;
	std::vector<DataTypeInt *>								m_sint_type_l;

};

} /* namespace vsc */

