/*
 * IModelField.h
 *
 *  Created on: Feb 8, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IAccept.h"
#include "vsc/IDataType.h"
#include "vsc/IModelConstraint.h"
#include "vsc/IModelVal.h"

namespace vsc {

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
using IModelFieldUP=std::unique_ptr<IModelField>;
class IModelField : public IAccept {
public:

	virtual ~IModelField() { }

	virtual const std::string &name() const = 0;

	virtual IDataType *getDataType() const = 0;

	virtual IModelField *getParent() const = 0;

	virtual void setParent(IModelField *p) = 0;

	virtual const std::vector<IModelConstraintUP> &constraints() const = 0;

	virtual void addConstraint(IModelConstraint *c) = 0;

	virtual const std::vector<IModelFieldUP> &fields() const = 0;

	virtual void addField(IModelField *field) = 0;

	virtual IModelField *getField(int32_t idx) = 0;

	virtual const IModelVal *val() const = 0;

	virtual IModelVal *val() = 0;

	virtual ModelFieldFlag flags() const = 0;

	virtual void clearFlag(ModelFieldFlag flags) = 0;

	virtual void setFlag(ModelFieldFlag flags) = 0;

	virtual bool isFlagSet(ModelFieldFlag flags) const = 0;

};

}
