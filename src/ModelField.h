/*
 * ModelField.h
 *
 *  Created on: Sep 24, 2021
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <string>
#include <vector>
#include "vsc/IDataType.h"
#include "vsc/IModelField.h"
#include "ModelConstraint.h"
#include "ModelVal.h"
#include "TypeField.h"

namespace vsc {

class ModelField;
using ModelFieldUP=std::unique_ptr<ModelField>;
class ModelField : public IModelField {
public:
	ModelField(IDataType *type);

	ModelField();

	virtual ~ModelField();

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

protected:
	IModelField						*m_parent;

	// Typically only really used for scalar fields
	ModelVal						m_val;

	std::vector<IModelFieldUP>		m_fields;
	std::vector<IModelConstraintUP>	m_constraints;
	ModelFieldFlag					m_flags;

};

} /* namespace vsc */

