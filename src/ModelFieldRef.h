/*
 * ModelFieldRef.h
 *
 *  Created on: May 10, 2022
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
#include "vsc/dm/IModelFieldRef.h"
#include "ModelField.h"

namespace vsc {
namespace dm {

class ModelFieldRef : public virtual IModelFieldRef {
public:
	ModelFieldRef();

	virtual ~ModelFieldRef();

	virtual IModelField *getParent() const override { return m_parent; }

	virtual void setParent(IModelField *p) override { m_parent = p; }

	virtual const std::vector<IModelConstraintUP> &getConstraints() const override {
		return m_ref->getConstraints();
	}

	virtual void addConstraint(
        IModelConstraint        *c,
        bool                    owned) override {
		m_ref->addConstraint(c, owned);
	}

	virtual const std::vector<IModelFieldUP> &getFields() const override {
		return m_ref->getFields();
	}

	virtual void addField(
        IModelField             *field,
        bool                    owned) override {
		m_ref->addField(field, owned);
	}

	virtual IModelField *getField(int32_t idx) override {
		return (m_ref)?m_ref->getField(idx):0;
	}

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

	virtual void setFieldData(IModelFieldData *data) override {
		m_data = IModelFieldDataUP(data);
	}

	virtual IModelFieldData *getFieldData() override {
		return m_data.get();
	}

	virtual void setRef(IModelField *ref) override {
		m_ref = ref;
	}

	virtual IModelField *getRef() const override {
		return m_ref;
	}

protected:
	IModelField						*m_parent;
	IModelFieldDataUP				m_data;
	ModelFieldFlag					m_flags;

private:
	IModelField						*m_ref;

};

}
} /* namespace vsc */

