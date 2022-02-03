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
#include "ModelVal.h"


namespace vsc {

using TypeFieldAttr=uint32_t;
static const TypeFieldAttr TypeFieldAttr_Rand = (1 << 0);

class DataTypeStruct;

class TypeField;
using TypeFieldUP=std::unique_ptr<TypeField>;
class TypeField : public virtual IAccept {
public:
	TypeField(
			DataTypeStruct		*parent,
			const std::string	&name,
			DataType			*type,
			TypeFieldAttr		attr,
			ModelVal			*init);

	virtual ~TypeField();

	const std::string &name() const { return m_name; }

	DataType *type() const { return m_type; }

	virtual void accept(IVisitor *v) { v->visitTypeField(this); }

protected:
	DataTypeStruct			*m_parent;
	std::string				m_name;
	DataType				*m_type;
	TypeFieldAttr			m_attr;
	ModelValUP				m_init;

};

} /* namespace vsc */

