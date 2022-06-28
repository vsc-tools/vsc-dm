/*
 * IDataTypeEnum.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IDataType.h"
#include "vsc/IDataTypeScalar.h"
#include "vsc/IModelVal.h"

namespace vsc {

class IDataTypeEnum;
using IDataTypeEnumUP=std::unique_ptr<IDataTypeEnum>;
class IDataTypeEnum : public virtual IDataTypeScalar {
public:

	virtual ~IDataTypeEnum() { }

	virtual bool isSigned() const = 0;

	virtual bool addEnumerator(
			const std::string	&name,
			const IModelVal		*val) = 0;

};

}
