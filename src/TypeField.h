/*
 * TypeField.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>
#include "DataType.h"
#include "vsc/IAccept.h"
#include "vsc/ITypeField.h"
#include "vsc/IModelVal.h"


namespace vsc {

class DataTypeStruct;

class TypeField;
using TypeFieldUP=std::unique_ptr<TypeField>;
class TypeField : public virtual ITypeField {
public:
	TypeField(
			const std::string	&name,
			IDataType			*type,
			bool				own_type,
			TypeFieldAttr		attr);

	virtual ~TypeField();

	virtual IDataTypeStruct *getParent() override { return m_parent; }

	virtual void setParent(IDataTypeStruct *p) override { m_parent = p; }

	const std::string &name() const { return m_name; }

	virtual IDataType *getDataType() const override { return m_type; }

	virtual void setDataType(IDataType *t) override { m_type = t; }

	virtual ITypeField *getField(int32_t idx) override;

	virtual TypeFieldAttr getAttr() const override { return m_attr; }

protected:
	IDataTypeStruct			*m_parent;
	std::string				m_name;
	IDataType				*m_type;
	IDataTypeUP				m_type_owned;
	TypeFieldAttr			m_attr;

};

} /* namespace vsc */

