/*
 * IDataTypeInt.h
 *
 *  Created on: Feb 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IDataTypeScalar.h"

namespace vsc {
namespace dm {

class IDataTypeInt;
using IDataTypeIntUP=UP<IDataTypeInt>;
class IDataTypeInt : public virtual IDataTypeScalar {
public:

	virtual ~IDataTypeInt() { }

	virtual bool is_signed() const = 0;

	virtual int32_t width() const = 0;

};

}
}
