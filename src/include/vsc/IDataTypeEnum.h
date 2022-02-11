/*
 * IDataTypeEnum.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IDataType.h"

namespace vsc {

class IDataTypeEnum;
using IDataTypeEnumUP=std::unique_ptr<IDataTypeEnum>;
class IDataTypeEnum : public IDataType {
public:

	virtual ~IDataTypeEnum() { }

};

}
