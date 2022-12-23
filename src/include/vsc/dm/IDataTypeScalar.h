/*
 * IDataTypeScalar.h
 *
 *  Created on: Jun 27, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IDataType.h"
#include "vsc/dm/ITypeExprRangelist.h"

namespace vsc {
namespace dm {

class IDataTypeScalar : public virtual IDataType {
public:

	virtual ~IDataTypeScalar() { }

	virtual ITypeExprRangelist *getDomain() = 0;

	virtual bool isSigned() const = 0;

	virtual int32_t getWidth() = 0;

};

}
}
