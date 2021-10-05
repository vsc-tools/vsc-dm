/*
 * ModelExprFieldRef.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once
#include "ModelExpr.h"
#include "ModelField.h"

namespace vsc {

class ModelExprFieldRef : public ModelExpr {
public:
	ModelExprFieldRef(ModelField *field);

	virtual ~ModelExprFieldRef();

	ModelField *field() const { return m_field; }

private:
	ModelField					*m_field;

};

} /* namespace vsc */

