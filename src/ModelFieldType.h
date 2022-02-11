/*
 * ModelFieldType.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelField.h"

namespace vsc {

/**
 * Field instance based on a field-type declaration
 */
class ModelFieldType : public ModelField {
public:
	ModelFieldType(TypeField *type);

	virtual ~ModelFieldType();

	virtual const std::string &name() const { return m_type->name(); }

	virtual IDataType *getDataType() const override { return m_type->type(); }

	virtual void accept(IVisitor *v) { v->visitModelFieldType(this); }

protected:
	TypeField					*m_type;

};

} /* namespace vsc */

