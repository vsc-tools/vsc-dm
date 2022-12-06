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
#include "ModelField.h"

namespace vsc {

class ModelFieldRoot;
using ModelFieldRootUP=std::unique_ptr<ModelFieldRoot>;

/**
 * Field instance based on a data type
 */
class ModelFieldRoot : public virtual IModelFieldRoot, public virtual ModelField {
public:
	ModelFieldRoot(
			IDataType			*type,
			const std::string	&name);

	virtual ~ModelFieldRoot();

	virtual const std::string &name() const override { return m_name; }

	virtual void setName(const std::string &name) { m_name = name; }

	virtual IDataType *getDataType() const override { return m_type; }

	virtual void setDataType(IDataType *t) override;

	virtual void accept(IVisitor *v) { v->visitModelFieldRoot(this); }

protected:
	IDataType					*m_type;
	std::string					m_name;
};

} /* namespace vsc */

