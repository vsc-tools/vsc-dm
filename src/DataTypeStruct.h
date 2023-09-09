/*
 * DataTypeStruct.h
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
#include <vector>
#include "vsc/dm/IDataTypeStruct.h"
#include "DataType.h"

namespace vsc {
namespace dm {

class TypeField;
using TypeFieldUP=std::unique_ptr<TypeField>;

class TypeConstraint;
using TypeConstraintUP=std::unique_ptr<TypeConstraint>;

class DataTypeStruct;
using DataTypeStructUP=std::unique_ptr<DataTypeStruct>;
class DataTypeStruct : public IDataTypeStruct, public virtual DataType {
public:
	DataTypeStruct(const std::string &name);

	virtual ~DataTypeStruct();

	virtual const std::string &name() const override {
		return m_name;
	}

	virtual void addField(
        ITypeField      *f,
        bool            owned) override;

	virtual const std::vector<ITypeFieldUP> &getFields() const override;

	virtual ITypeField *getField(int32_t idx) override;

    virtual int32_t getNumBuiltin() const { return 0; }

    virtual void initVal(ValRef &v) override;

    virtual void finiVal(ValRef &v) override;

    virtual ValRef copyVal(const ValRef &src) override;

	virtual void addConstraint(
        ITypeConstraint     *c,
        bool                owned) override;

	virtual const std::vector<ITypeConstraintUP> &getConstraints() const override;

	virtual IModelStructCreateHook *getCreateHook() const override {
		return m_create_hook.get();
	}

	virtual void setCreateHook(
        IModelStructCreateHook      *hook,
        bool                        owned) override {
		m_create_hook = IModelStructCreateHookUP(hook, owned);
	}

	virtual IModelField *mkRootField(
		IModelBuildContext	*ctxt,
		const std::string	&name,
		bool				is_ref) override;

	virtual IModelField *mkTypeField(
		IModelBuildContext	*ctxt,
		ITypeField			*type,
        const ValRef        &val) override;

	virtual void accept(IVisitor *v) override { v->visitDataTypeStruct(this); }

private:
	std::string							m_name;
	std::vector<ITypeFieldUP>			m_fields;
	std::vector<ITypeConstraintUP>		m_constraints;
	IModelStructCreateHookUP			m_create_hook;

};

}
} /* namespace vsc */

