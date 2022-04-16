/*
 * TypeExprVal.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeExprVal.h"
#include "ModelVal.h"


namespace vsc {

class TypeExprVal : public ITypeExprVal {
public:
	TypeExprVal(const IModelVal *v);

	virtual ~TypeExprVal();

	virtual IModelVal *val() {
		return &m_val;
	}

	virtual void accept(IVisitor *v) override { v->visitTypeExprVal(this); }

private:
	ModelVal				m_val;
};

} /* namespace vsc */

