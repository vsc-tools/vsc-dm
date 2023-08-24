/*
 * ModelFieldType.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 * 
 * Copyright 2019-2023 Matthew Ballance and contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 */

#pragma once
#include "vsc/dm/IModelFieldType.h"
#include "ModelField.h"

namespace vsc {
namespace dm {

/**
 * Field instance based on a field-type declaration
 */
class ModelFieldType : public virtual IModelFieldType {
public:
	ModelFieldType(
        ITypeField      *type,
        const ValRef    &val);

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

	virtual const std::vector<IModelConstraintUP> &getConstraints() const override {
		return m_constraints;
	}

	virtual void addConstraint(
        IModelConstraint        *c,
        bool                    owned) override;

	virtual const std::vector<IModelFieldUP> &getFields() const override {
		return m_fields;
	}

	virtual void addField(
        IModelField             *field,
        bool                    owned) override;

	virtual IModelField *getField(int32_t idx) override;

    virtual ValRef &&getVal(bool mut=false) const override;

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

    // Reference to value storage for this field
    ValRef                          m_val;

	std::vector<IModelFieldUP>		m_fields;
	std::vector<IModelConstraintUP>	m_constraints;
	ModelFieldFlag					m_flags;
	IModelFieldDataUP				m_field_data;

};

}
} /* namespace vsc */

