/*
 * ModelFieldType.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelFieldType.h"
#include "ModelField.h"

namespace vsc {
namespace dm {

/**
 * Field instance based on a field-type declaration
 */
class ModelFieldType : public IModelFieldType {
public:
	ModelFieldType(ITypeField *type);

	virtual ~ModelFieldType();

	virtual const std::string &name() const override { return m_type->name(); }


	virtual IDataType *getDataType() const override { return m_type->getDataType(); }

	// Ignore
	virtual void setDataType(IDataType *t) override { }

	virtual IModelField *getParent() const override { return m_parent; }

	virtual void setParent(IModelField *p) override { m_parent = p; }

	virtual ITypeField *getTypeField() const override {
		return m_type;
	}

	virtual const std::vector<IModelConstraintUP> &constraints() const override {
		return m_constraints;
	}

	virtual void addConstraint(IModelConstraint *c) override;

	virtual const std::vector<IModelFieldUP> &fields() const override {
		return m_fields;
	}

	virtual void addField(IModelField *field) override;

	virtual IModelField *getField(int32_t idx) override;

	virtual const IModelVal *val() const override {
		return &m_val;
	}

	virtual IModelVal *val() override {
		return &m_val;
	}

	virtual ModelFieldFlag flags() const override { return m_flags; }

	virtual void clearFlag(ModelFieldFlag flags) override {
		m_flags = (m_flags & (~flags));
	}

	virtual void setFlag(ModelFieldFlag flags) override {
		m_flags = (m_flags | flags);
	}

	virtual void setFlags(ModelFieldFlag flags) override {
		m_flags = flags;
	}

	virtual bool isFlagSet(ModelFieldFlag flags) const override {
		return ((m_flags & flags) == flags);
	}

	virtual void setFieldData(IModelFieldData *data) override;

	virtual IModelFieldData *getFieldData() override;

	virtual void accept(IVisitor *v) { v->visitModelFieldType(this); }

protected:
	ITypeField						*m_type;
	IModelField						*m_parent;

	// Typically only really used for scalar fields
	ModelVal						m_val;

	std::vector<IModelFieldUP>		m_fields;
	std::vector<IModelConstraintUP>	m_constraints;
	ModelFieldFlag					m_flags;
	IModelFieldDataUP				m_field_data;

};

}
} /* namespace vsc */

