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
	DataTypeEnum(
			const std::string		&name,
			bool 					is_signed);

	virtual ~DataTypeEnum();

	const std::string &name() const override {
		return m_name;
	}

	bool isSigned() const override {
		return m_is_signed;
	}

	virtual int32_t getWidth() override;

	virtual bool addEnumerator(
			const std::string	&name,
			const IModelVal		*val) override;

	virtual ITypeExprRangelist *getDomain() override;

	virtual void accept(IVisitor *v) override { v->visitDataTypeEnum(this); }

private:
	std::string										m_name;
	bool											m_is_signed;
	std::unordered_map<std::string,ModelVal>		m_enum_val_m;
	std::unordered_map<ModelVal,std::string>		m_val_enum_m;
	ITypeExprRangelistUP							m_domain;
	int32_t											m_width;

};

} /* namespace vsc */

