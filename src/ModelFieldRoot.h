/*
 * ModelFieldRoot.h
 *
 *  Created on: Sep 26, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelField.h"

namespace vsc {

class ModelFieldRoot;
using ModelFieldRootUP=std::unique_ptr<ModelFieldRoot>;

/**
 * Field instance based on a data type
 */
class ModelFieldRoot : public ModelField {
public:
	ModelFieldRoot(
			DataType			*type,
			const std::string	&name
			);

	virtual ~ModelFieldRoot();

	virtual const std::string &name() const { return m_name; }

	virtual DataType *datatype() const { return m_type; }

	virtual void accept(IVisitor *v) { v->visitModelFieldRoot(this); }

protected:
	DataType					*m_type;
	std::string					m_name;


};

} /* namespace vsc */

