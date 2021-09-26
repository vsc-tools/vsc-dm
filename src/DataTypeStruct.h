/*
 * DataTypeStruct.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "DataType.h"

namespace vsc {

class TypeField;
using TypeFieldUP=std::unique_ptr<TypeField>;

class TypeConstraint;
using TypeConstraintUP=std::unique_ptr<TypeConstraint>;

class DataTypeStruct;
using DataTypeStructUP=std::unique_ptr<DataTypeStruct>;
class DataTypeStruct : public DataType {
public:
	DataTypeStruct(const std::string &name);

	virtual ~DataTypeStruct();

	const std::string &name() const { return m_name; }

private:
	std::string							m_name;
	std::vector<TypeFieldUP>			m_fields;
	std::vector<TypeConstraintUP>		m_constraints;

};

} /* namespace vsc */

