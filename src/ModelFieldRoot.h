/*
 * ModelFieldRoot.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#pragma once
#include <string>
#include "vsc/IModelFieldRoot.h"
#include "ModelVal.h"

namespace vsc {

class ModelFieldRoot;
using ModelFieldRootUP=std::unique_ptr<ModelFieldRoot>;

/**
 * Field instance based on a data type
 */
class ModelFieldRoot : public IModelFieldRoot {
public:
	ModelFieldRoot(
			IDataType			*type,
			const std::string	&name);

	virtual ~ModelFieldRoot();

	virtual const std::string &name() const override { return m_name; }

	virtual void setName(const std::string &name) { m_name = name; }

	virtual IDataType *getDataType() const override { return m_type; }

	virtual IModelField *getParent() const override { return m_parent; }

	virtual void setParent(IModelField *p) override { m_parent = p; }

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

	virtual bool isFlagSet(ModelFieldFlag flags) const override {
		return ((m_flags & flags) == flags);
	}

	virtual void setFieldData(IModelFieldData *data) override;

	virtual IModelFieldData *getFieldData() override;

	virtual void accept(IVisitor *v) { v->visitModelFieldRoot(this); }

protected:
	IDataType					*m_type;
	std::string					m_name;
	IModelField						*m_parent;

	// Typically only really used for scalar fields
	ModelVal						m_val;

	std::vector<IModelFieldUP>		m_fields;
	std::vector<IModelConstraintUP>	m_constraints;
	ModelFieldFlag					m_flags;
	IModelFieldDataUP				m_field_data;

};

} /* namespace vsc */

