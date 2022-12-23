/*
 * DataTypeInt.h
 *
 *  Created on: Sep 23, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IDataTypeInt.h"
#include "vsc/dm/ITypeExprRangelist.h"
#include "DataType.h"

namespace vsc {
namespace dm {

class DataTypeInt;
using DataTypeIntUP=std::unique_ptr<DataTypeInt>;
class DataTypeInt : public virtual IDataTypeInt, public virtual DataType {
public:
	DataTypeInt(
			bool			is_signed,
			int32_t			width);

	virtual ~DataTypeInt();

	virtual bool is_signed() const override { return m_is_signed; }

	virtual bool isSigned() const override { return m_is_signed; }

	virtual int32_t width() const override { return m_width; }

	virtual int32_t getWidth() override { return m_width; }

	virtual ITypeExprRangelist *getDomain() override;

	virtual IModelField *mkRootField(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) override;

	virtual IModelField *mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type) override;

	virtual void accept(IVisitor *v) { v->visitDataTypeInt(this); }

protected:
	bool					m_is_signed;
	int32_t					m_width;
	ITypeExprRangelistUP	m_domain;
};

}
} /* namespace vsc */

