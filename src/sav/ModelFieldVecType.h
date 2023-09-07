/*
 * ModelFieldVecType.h
 *
 *  Created on: Jul 2, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeField.h"
#include "ModelFieldVec.h"

namespace vsc {
namespace dm {

class ModelFieldVecType : public ModelFieldVec {
public:
	ModelFieldVecType(
			IContext		*ctxt,
			ITypeField		*type);

	virtual ~ModelFieldVecType();

	virtual const std::string &name() const override {
		return m_type->name();
	}

	virtual IDataType *getDataType() const override {
		return m_type->getDataType();
	}

private:
	ITypeField				*m_type;
};

}
} /* namespace vsc */

