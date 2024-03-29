/*
 * ModelField.h
 *
 *  Created on: Sep 24, 2021
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
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "vsc/dm/IDataType.h"
#include "vsc/dm/IModelField.h"
#include "ModelConstraint.h"
#include "ModelVal.h"
#include "TypeField.h"

namespace vsc {
namespace dm {

class ModelField;
using ModelFieldUP=std::unique_ptr<ModelField>;
class ModelField : public virtual IModelField {
public:
	ModelField(IDataType *type);

	ModelField();

	virtual ~ModelField();

	virtual IModelField *getParent() const override { return m_parent; }

	virtual void setParent(IModelField *p) override { m_parent = p; }

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

    virtual ValRef getImmVal() const override {
        return m_val.toImmutable();
    }

    virtual ValRef getMutVal() const override {
        return m_val.toMutable();
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

protected:
	IModelField						*m_parent;

    // Handle to the value storage for this field
	ValRef						    m_val;

	std::vector<IModelFieldUP>		m_fields;
	std::vector<IModelConstraintUP>	m_constraints;
	ModelFieldFlag					m_flags;
	IModelFieldDataUP				m_data;

};

}
} /* namespace vsc */

