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
using IDataTypeSP=std::shared_ptr<IDataType>;
class IDataType : public IAccept {
public:

	virtual ~IDataType() { }

	// Notify datatype that no more information
	// will be added.
	virtual void finalize() = 0;


};

}

