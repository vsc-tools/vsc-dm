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
            ValRef              &&init);

	virtual ~TypeFieldPhy();

	virtual const ValRef &getInit() const override { 
        return m_init;
    }

	virtual void accept(IVisitor *v) { v->visitTypeFieldPhy(this); }

private:
    ValRef                 m_init;

};

}
} /* namespace vsc */

