/*
 * TypeFieldVec.h
 *
 *  Created on: Jul 2, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IContext.h"
#include "vsc/dm/ITypeFieldVec.h"
#include "TypeField.h"

namespace vsc {
namespace dm {

class TypeFieldVec : public virtual ITypeFieldVec, public virtual TypeField {
public:
	TypeFieldVec(
			IContext				*ctxt,
			const std::string		&name,
			IDataType				*type,
			bool					own_type,
			TypeFieldAttr			attr,
			IModelVal				*init_sz);

	virtual ~TypeFieldVec();

	virtual ITypeField *getSizeRef() const override { return m_size.get(); }

	virtual IModelVal *getInitSize() const override { return m_init_sz.get(); }

	virtual void accept(IVisitor *v) override { v->visitTypeFieldVec(this); }

private:
	ITypeFieldUP						m_size;
	IModelValUP							m_init_sz;
};

}
} /* namespace vsc */

