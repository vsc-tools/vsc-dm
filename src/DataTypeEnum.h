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
#include "vsc/dm/IDataTypeEnum.h"
#include "vsc/dm/ITypeExprRangelist.h"
#include "DataType.h"
#include "ModelVal.h"

namespace vsc {
namespace dm {

class DataTypeEnum : public virtual IDataTypeEnum, public virtual DataType {
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

    virtual void initVal(ValRef &v) override;

    virtual void finiVal(ValRef &v) override;

    virtual ValRef copyVal(const ValRef &src) override;

	virtual bool addEnumerator(
			const std::string	&name,
			const IModelVal		*val) override;

	virtual ITypeExprRangelist *getDomain() override;

	virtual IModelField *mkRootField(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) override;

	virtual IModelField *mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type,
        const ValRef        &val) override;

	virtual void accept(IVisitor *v) override { v->visitDataTypeEnum(this); }

private:
	std::string										m_name;
	bool											m_is_signed;
	std::unordered_map<std::string,ModelVal>		m_enum_val_m;
	std::unordered_map<ModelVal,std::string>		m_val_enum_m;
	ITypeExprRangelistUP							m_domain;
	int32_t											m_width;

};

}
} /* namespace vsc */

