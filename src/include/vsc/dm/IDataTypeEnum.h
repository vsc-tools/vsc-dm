/*
 * IDataTypeEnum.h
 *
 *  Created on: Feb 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IDataType.h"
#include "vsc/dm/IDataTypeScalar.h"
#include "vsc/dm/IModelVal.h"

namespace vsc {
namespace dm {

class IDataTypeEnum;
using IDataTypeEnumUP=UP<IDataTypeEnum>;
class IDataTypeEnum : public virtual IDataTypeScalar {
public:

	virtual ~IDataTypeEnum() { }

	virtual const std::string &name() const = 0;

	virtual bool addEnumerator(
			const std::string	&name,
			const IModelVal		*val) = 0;

};

}
}
