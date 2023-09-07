/*
 * IModelField.h
 *
 *  Created on: Feb 8, 2022
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
#include "vsc/dm/IAccept.h"
#include "vsc/dm/IDataType.h"
#include "vsc/dm/IModelConstraint.h"
#include "vsc/dm/IModelFieldData.h"
#include "vsc/dm/IModelVal.h"
#include "vsc/dm/impl/ValRef.h"

namespace vsc {
namespace dm {

enum class ModelFieldFlag {
	NoFlags  = 0,
	DeclRand = (1 << 0),
	UsedRand = (1 << 1),
	Resolved = (1 << 2),
	VecSize  = (1 << 3)
};

static inline ModelFieldFlag operator | (const ModelFieldFlag lhs, const ModelFieldFlag rhs) {
	return static_cast<ModelFieldFlag>(
			static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

static inline ModelFieldFlag operator |= (ModelFieldFlag &lhs, const ModelFieldFlag rhs) {
	lhs = static_cast<ModelFieldFlag>(
			static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
	return lhs;
}

static inline ModelFieldFlag operator & (const ModelFieldFlag lhs, const ModelFieldFlag rhs) {
	return static_cast<ModelFieldFlag>(
			static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

static inline ModelFieldFlag operator ~ (const ModelFieldFlag lhs) {
	return static_cast<ModelFieldFlag>(~static_cast<uint32_t>(lhs));
}

class IModelField;
using IModelFieldUP=UP<IModelField>;
class IModelField : public virtual IAccept {
public:

	virtual ~IModelField() { }

	virtual const std::string &name() const = 0;

	virtual IDataType *getDataType() const = 0;

	template <class T> T *getDataTypeT() const {
		return dynamic_cast<T *>(getDataType());
	}

	virtual void setDataType(IDataType *t) = 0;

	virtual IModelField *getParent() const = 0;

	template <class T> T *getParentT() const {
		return dynamic_cast<T *>(getParent());
	}

	virtual void setParent(IModelField *p) = 0;

	virtual const std::vector<IModelConstraintUP> &getConstraints() const = 0;

	virtual void addConstraint(
        IModelConstraint    *c,
        bool                owned=true) = 0;

	virtual const std::vector<IModelFieldUP> &getFields() const = 0;

	virtual void addField(
        IModelField     *field,
        bool            owned=true) = 0;

	virtual IModelField *getField(int32_t idx) = 0;

	template <class T> T *getFieldT(int32_t idx) {
		return dynamic_cast<T *>(getField(idx));
	}

    /**
     * @brief Returns a value ref that either allows or prohibits
     * the caller from mutating the storage used by the field
     * 
     * @return ValRef 
     */
    virtual ValRef getImmVal() const = 0;

    virtual ValRef getMutVal() const = 0;

	virtual ModelFieldFlag flags() const = 0;

	virtual void clearFlag(ModelFieldFlag flags) = 0;

	virtual void setFlag(ModelFieldFlag flags) = 0;

	virtual void setFlags(ModelFieldFlag flags) = 0;

	virtual bool isFlagSet(ModelFieldFlag flags) const = 0;

	virtual void setFieldData(IModelFieldData *data) = 0;

	virtual IModelFieldData *getFieldData() = 0;

};

}
}
