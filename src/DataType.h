/*
 * DataType.h
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IDataType.h"
#include "ModelVal.h"

namespace vsc {

class DataType;
typedef std::unique_ptr<DataType> DataTypeUP;
class DataType : public IDataType {
public:
	DataType();

	virtual ~DataType();

#ifdef UNDEFINED
	/**
	 * Obtain the initial value of this data type
	 */
	virtual void initial(IModelVal *v) = 0;

	virtual bool eq(
			DataType						*other_t,
			const std::vector<uint32_t>		val) = 0;
#endif

private:

};

} /* namespace vsc */

