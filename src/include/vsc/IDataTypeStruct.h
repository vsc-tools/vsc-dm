/*
 * IDataTypeStruct.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IDataType.h"

namespace vsc {

class IDataTypeStruct;
using IDataTypeStructUP=std::unique_ptr<IDataTypeStruct>;
class IDataTypeStruct : public IDataType {
public:

	virtual ~IDataTypeStruct() { }

	virtual const std::string &name() const = 0;
};

}

