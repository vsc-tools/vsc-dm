/*
 * IDataTypeInt.h
 *
 *  Created on: Feb 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IDataType.h"

namespace vsc {

class IDataTypeInt;
using IDataTypeIntUP=std::unique_ptr<IDataTypeInt>;
class IDataTypeInt : public virtual IDataType {
public:

	virtual ~IDataTypeInt() { }

	virtual bool is_signed() const = 0;

	virtual int32_t width() const = 0;

};

}
