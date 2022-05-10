/*
 * TypeFieldRef.h
 *
 *  Created on: May 9, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeFieldRef.h"

namespace vsc {

class TypeFieldRef : public ITypeFieldRef {
public:
	TypeFieldRef(
			const std::string		&name,
			IDataType				*type,
			TypeFieldAttr			attr);

	virtual ~TypeFieldRef();

	virtual IDataTypeStruct *getParent() override { return m_parent; }

	virtual void setParent(IDataTypeStruct *p) override { m_parent = p; }

	virtual const std::string &name() const { return m_name; }

	virtual IDataType *getDataType() const { return m_type; }

	virtual TypeFieldAttr getAttr() const { return m_attr; }

	virtual void accept(IVisitor *v) override { v->visitTypeFieldRef(this); }

private:
	IDataTypeStruct				*m_parent;

	std::string					m_name;
	IDataType					*m_type;
	TypeFieldAttr				m_attr;

};

} /* namespace vsc */

