/*
 * TypeFieldPhy.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeFieldPhy.h"
#include "TypeField.h"

namespace vsc {
namespace dm {

class TypeFieldPhy : 
    public virtual ITypeFieldPhy, 
    public TypeField {
public:
	TypeFieldPhy(
			const std::string	&name,
			IDataType			*type,
			bool				own_type,
			TypeFieldAttr		attr,
			ITypeExpr			*init);

	virtual ~TypeFieldPhy();

	virtual ITypeExpr *getInit() override { 
        return m_init.get();
    }

	virtual void accept(IVisitor *v) { v->visitTypeFieldPhy(this); }

private:
    ITypeExprUP					m_init;

};

}
} /* namespace vsc */

