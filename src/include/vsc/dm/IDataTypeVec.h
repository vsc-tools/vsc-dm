/*
 * IDataTypeVec.h
 *
 *  Created on: Jul 2, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/dm/IDataType.h"

namespace vsc {
namespace dm {

class IDataTypeVec;
using IDataTypeVecUP=UP<IDataTypeVec>;
class IDataTypeVec : public virtual IDataType {
public:

	virtual ~IDataTypeVec() { }

	virtual IDataType *getElemType() const = 0;

};

}
}
