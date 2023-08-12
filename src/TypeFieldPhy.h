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
            ValData             init,
            bool                have_init);

	virtual ~TypeFieldPhy();

    virtual bool haveInit() const override {
        return m_haveInit;
    }

	virtual ValData getInit() const override { 
        return m_init;
    }

	virtual void accept(IVisitor *v) { v->visitTypeFieldPhy(this); }

private:
    ValData                 m_init;
    bool                    m_haveInit;

};

}
} /* namespace vsc */

