/*
 * TypeFieldPhy.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeFieldPhy.h"
#include "TypeField.h"

namespace vsc {

class TypeFieldPhy : public virtual ITypeFieldPhy, public TypeField {
public:
	TypeFieldPhy(
			const std::string	&name,
			IDataType			*type,
			bool				own_type,
			TypeFieldAttr		attr,
			IModelVal			*init);

	virtual ~TypeFieldPhy();

	virtual IModelVal *getInit() const override { return m_init.get(); }

	virtual void accept(IVisitor *v) { v->visitTypeField(this); }

private:
	IModelValUP				m_init;

};

} /* namespace vsc */

