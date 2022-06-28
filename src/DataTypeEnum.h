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
#include <unordered_map>
#include "vsc/IDataTypeEnum.h"
#include "vsc/ITypeExprRangelist.h"
#include "ModelVal.h"

namespace vsc {

class DataTypeEnum : public IDataTypeEnum {
public:
	DataTypeEnum();

	virtual ~DataTypeEnum();

	virtual bool addEnumerator(
			const std::string	&name,
			const IModelVal		*val) override;

	virtual ITypeExprRangelist *getDomain() override;

private:
	std::unordered_map<std::string,ModelVal>		m_enum_val_m;
	std::unordered_map<ModelVal,std::string>		m_val_enum_m;
	ITypeExprRangelistUP							m_domain;

};

} /* namespace vsc */

