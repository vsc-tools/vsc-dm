/*
 * ITypeField.h
 *
 *  Created on: Apr 5, 2022
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
#include "vsc/dm/IAccept.h"
#include "vsc/dm/IDataType.h"
#include "vsc/dm/TypeFieldAttr.h"
#include "vsc/dm/ITypeVar.h"
#include "vsc/dm/IModelVal.h"
#include "vsc/dm/IModelBuildContext.h"

namespace vsc {
namespace dm {

class IDataTypeStruct;

class ITypeField;
using ITypeFieldUP=UP<ITypeField>;
class ITypeField : 
    public virtual ITypeVar,
    public virtual IAccept {
public:

	virtual ~ITypeField() { }

	virtual ITypeField *getParent() const = 0;

	virtual void setParent(ITypeField *p) = 0;

	virtual int32_t getIndex() const = 0;

	virtual void setIndex(int32_t) = 0;

    virtual int32_t getOffset() const = 0;

    virtual void setOffset(int32_t off) = 0;

    virtual int32_t getByteSize() const = 0;

    virtual bool isDataTypeOwned() const = 0;

	virtual void setDataType(IDataType *t, bool owned=false) = 0;

	virtual ITypeField *getField(int32_t idx) const = 0;

	template <class T> T *getFieldT(int32_t idx) const {
		return dynamic_cast<T *>(getField(idx));
	}

	virtual TypeFieldAttr getAttr() const = 0;

	virtual IModelField *mkModelField(
		IModelBuildContext 			*ctxt,
        const ValRef                &val) = 0;

	template <class T> T *mkModelFieldT(
		IModelBuildContext 			*ctxt,
        const ValRef                &val) {
		return dynamic_cast<T *>(mkModelField(ctxt, val));
	}

};

}
}
