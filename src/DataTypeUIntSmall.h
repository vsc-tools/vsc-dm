/*
 * DataTypeUIntSmall.h
 *
 *  Created on: Sep 25, 2021
 *      Author: mballance
 */

#pragma once
#include "DataTypeInt.h"

namespace vsc {

class DataTypeUIntSmall : public DataTypeInt {
public:
	DataTypeUIntSmall(
			int32_t			width);

	virtual ~DataTypeUIntSmall();

};

} /* namespace vsc */

