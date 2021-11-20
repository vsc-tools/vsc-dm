/*
 * DataTypeInt.h
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#pragma once
#include "DataType.h"
#include "IDataTypeInt.h"

namespace vsc {

class DataTypeInt;
using DataTypeIntUP=std::unique_ptr<DataTypeInt>;
class DataTypeInt : public DataType {
public:
	DataTypeInt(
			bool			is_signed,
			int32_t			width);

	virtual ~DataTypeInt();

	bool is_signed() const { return m_is_signed; }

	int32_t width() const { return m_width; }

	virtual void accept(IVisitor *v) { v->visitDataTypeInt(this); }

protected:
	bool					m_is_signed;
	int32_t					m_width;
};

} /* namespace vsc */

