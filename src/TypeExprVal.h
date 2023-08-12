/*
 * TypeExprVal.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeExprVal.h"
#include "ModelVal.h"


namespace vsc {
namespace dm {

class TypeExprVal : public ITypeExprVal {
public:
	TypeExprVal(IDataType *type, ValData v);

	virtual ~TypeExprVal();

	virtual ValData val() {
		return m_val;
	}

	virtual void accept(IVisitor *v) override { v->visitTypeExprVal(this); }

private:
    IDataType               *m_type;
    ValData                 m_val;
};

}
} /* namespace vsc */

