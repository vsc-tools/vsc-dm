/*
 * TypeExprVal.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeExprVal.h"
#include "vsc/dm/impl/ValRef.h"
#include "ModelVal.h"


namespace vsc {
namespace dm {

class TypeExprVal : public ITypeExprVal {
public:
	TypeExprVal(IDataType *type, ValData v);

	TypeExprVal(const ValRef &v);

	virtual ~TypeExprVal();

	virtual const ValRef &val() const {
		return m_val;
	}

    virtual IDataType *type() const {
        return m_val.type();
    }

	virtual void accept(IVisitor *v) override { v->visitTypeExprVal(this); }

private:
    ValRef                  m_val;
};

}
} /* namespace vsc */

