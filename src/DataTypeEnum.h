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

	virtual int32_t addEnumerator(
			const std::string	&name,
            const ValRef        &val) override;

    virtual int32_t numEnumerators() override {
        return m_enumerators.size();
    }

    virtual std::pair<std::string,ValRef> getEnumerator(int32_t idx) override {
        return m_enumerators.at(idx);
    }

    virtual int32_t getEnumeratorId(const std::string &name) override;

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
	std::unordered_map<std::string,int32_t>		    m_enum_id_m;
	std::unordered_map<ModelVal,std::string>		m_val_enum_m;
    std::vector<std::pair<std::string,ValRef>>      m_enumerators;
	ITypeExprRangelistUP							m_domain;
	int32_t											m_width;

};

}
} /* namespace vsc */

