/*
 * IDataTypeStruct.h
 *
 *  Created on: Feb 10, 2022
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
#include <string>
#include <vector>
#include "vsc/dm/IDataType.h"
#include "vsc/dm/IModelFieldFactory.h"
#include "vsc/dm/IModelStructCreateHook.h"
#include "vsc/dm/ITypeConstraint.h"
#include "vsc/dm/ITypeField.h"

namespace vsc {
namespace dm {

class IDataTypeStruct;
using IDataTypeStructUP=UP<IDataTypeStruct>;
class IDataTypeStruct : public virtual IDataType {
public:

	virtual ~IDataTypeStruct() { }

	virtual const std::string &name() const = 0;

	virtual void addField(
        ITypeField      *f,
        bool            owned=true) = 0;

	virtual const std::vector<ITypeFieldUP> &getFields() const = 0;

    /**
     * @brief Returns a 'user' field with a >= idx. Returns a 'impl' field with <0 idx.
     */
	virtual ITypeField *getField(int32_t idx) = 0;

    virtual int32_t getNumBuiltin() const = 0;

    /**
     * The 'super' type provides meta-data about the type. It is used 
     * by downstream tools to change processing based on inheritance
     * relationships. Each type definition is fully independent such 
     * that the inheritance relationships need not be present to
     * reconstruct the content of a given type.
     */
    virtual IDataTypeStruct *getSuper() = 0;

    virtual void setSuper(IDataTypeStruct *t, bool owned=false) = 0;

	template <class T> T *getFieldT(int32_t idx) {
		return dynamic_cast<T *>(getField(idx));
	}

	virtual void addConstraint(
        ITypeConstraint     *c,
        bool                owned=true) = 0;

	virtual const std::vector<ITypeConstraintUP> &getConstraints() const = 0;

	virtual IModelStructCreateHook *getCreateHook() const = 0;

	virtual void setCreateHook(
        IModelStructCreateHook *hook,
        bool                    owned=true) = 0;

};

}
}

