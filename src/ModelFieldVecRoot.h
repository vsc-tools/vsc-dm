/*
 * ModelFieldVecRoot.h
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#pragma once
#include "DataType.h"
#include "ModelFieldVec.h"

namespace vsc {

class ModelFieldVecRoot : public ModelFieldVec {
public:
	ModelFieldVecRoot(
			DataType				*type,
			const std::string		&name,
			ModelField				*size);

	virtual ~ModelFieldVecRoot();

	virtual const std::string &name() const override { return m_name; }

	virtual DataType *datatype() const override { return m_type; }

	virtual void accept(IVisitor *v) override { v->visitModelFieldVecRoot(this); }

protected:
	DataType					*m_type;
	std::string					m_name;
};

} /* namespace vsc */

