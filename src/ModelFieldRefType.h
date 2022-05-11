/*
 * ModelFieldRefType.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeField.h"
#include "ModelFieldRef.h"

namespace vsc {

class ModelFieldRefType : public ModelFieldRef {
public:
	ModelFieldRefType(ITypeField *type);

	virtual ~ModelFieldRefType();

	virtual const std::string &name() const override {
		return m_type->name();
	}

	virtual IDataType *getDataType() const override {
		return m_type->getDataType();
	}

	virtual void accept(IVisitor *v) override { v->visitModelFieldRefType(this); }

private:
	ITypeField					*m_type;
};

} /* namespace vsc */

