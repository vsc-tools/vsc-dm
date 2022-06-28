/*
 * DataTypeInt.h
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IDataTypeInt.h"
#include "DataType.h"

namespace vsc {

class DataTypeInt;
using DataTypeIntUP=std::unique_ptr<DataTypeInt>;
class DataTypeInt : public IDataTypeInt, public virtual DataType {
public:
	DataTypeInt(
			bool			is_signed,
			int32_t			width);

	virtual ~DataTypeInt();

	virtual bool is_signed() const override { return m_is_signed; }

	virtual int32_t width() const override { return m_width; }

	virtual void accept(IVisitor *v) { v->visitDataTypeInt(this); }

protected:
	bool					m_is_signed;
	int32_t					m_width;
};

} /* namespace vsc */

