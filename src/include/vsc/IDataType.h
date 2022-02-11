/*
 * IDataType.h
 *
 *  Created on: Feb 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IAccept.h"

namespace vsc {

class IDataType;
using IDataTypeUP=std::unique_ptr<IDataType>;
class IDataType : public IAccept{
public:

	virtual ~IDataType() { }


};

}

