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

	virtual int32_t width() const override {
		return m_field->val().bits();
	}

	ModelField *field() const { return m_field; }

	virtual void accept(IVisitor *v) { v->visitModelExprFieldRef(this); }

private:
	ModelField					*m_field;

};

} /* namespace vsc */

