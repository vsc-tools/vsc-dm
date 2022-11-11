/*
 * ModelFieldRefType.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeField.h"
#include "vsc/IModelFieldTypeRef.h"
#include "ModelFieldRef.h"

namespace vsc {

class ModelFieldRefType : 
	public virtual IModelFieldTypeRef, 
	public virtual ModelFieldRef {
public:
	ModelFieldRefType(ITypeField *type);

	virtual ~ModelFieldRefType();

	virtual const std::string &name() const override {
		return m_type->name();
	}

	virtual ITypeField *getTypeField() const override {
		return m_type;
	}

	virtual IDataType *getDataType() const override {
		return m_type->getDataType();
	}

    virtual IDataType *getDataTypeRef() const override {
		return m_type->getDataType();
	}

	virtual void accept(IVisitor *v) override { v->visitModelFieldRefType(this); }

private:
	ITypeField					*m_type;
};

} /* namespace vsc */

