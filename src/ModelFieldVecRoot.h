/*
 * ModelFieldVecRoot.h
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelFieldVecRoot.h"
#include "DataType.h"
#include "ModelFieldVec.h"

namespace vsc {

class ModelFieldVecRoot : public ModelFieldVec, public IModelFieldVecRoot {
public:
	ModelFieldVecRoot(
			IDataType				*type,
			const std::string		&name,
			IModelField				*size);

	virtual ~ModelFieldVecRoot();

	virtual const std::string &name() const override { return m_name; }

	virtual IDataType *getDataType() const override { return m_type; }

	virtual void accept(IVisitor *v) override { v->visitModelFieldVecRoot(this); }

protected:
	IDataType					*m_type;
	std::string					m_name;
};

} /* namespace vsc */

