/*
 * DataTypeEnum.h
 *
 *  Created on: Nov 3, 2021
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include <vector>
#include <string>
#include "vsc/IDataTypeEnum.h"

namespace vsc {

class DataTypeEnum : public IDataTypeEnum {
public:
	DataTypeEnum();

	virtual ~DataTypeEnum();

private:
	std::vector<std::pair<int64_t,std::string>>		m_domain;

};

} /* namespace vsc */

