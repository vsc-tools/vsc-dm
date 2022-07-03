/*
 * IDataTypeVec.h
 *
 *  Created on: Jul 2, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IDataType.h"

namespace vsc {

class IDataTypeVec;
using IDataTypeVecUP=std::unique_ptr<IDataTypeVec>;
class IDataTypeVec : public virtual IDataType {
public:

	virtual ~IDataTypeVec() { }

	virtual IDataType *getElemType() const = 0;

};

}
