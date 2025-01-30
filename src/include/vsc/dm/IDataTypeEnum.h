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
#include "vsc/dm/impl/ValRef.h"

namespace vsc {
namespace dm {

class IDataTypeEnum;
using IDataTypeEnumUP=UP<IDataTypeEnum>;
class IDataTypeEnum : public virtual IDataTypeScalar {
public:

	virtual ~IDataTypeEnum() { }

	virtual const std::string &name() const = 0;

	virtual int32_t addEnumerator(
			const std::string	&name,
			const ValRef		&val) = 0;

    virtual int32_t numEnumerators() = 0;

    virtual std::pair<std::string,ValRef> getEnumerator(int32_t idx) = 0;

    virtual int32_t getEnumeratorId(const std::string &name) = 0;

};

}
}
