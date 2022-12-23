/*
 * TypeFieldRef.h
 *
 *  Created on: May 9, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeFieldRef.h"
#include "TypeField.h"

namespace vsc {
namespace dm {

class TypeFieldRef : public virtual ITypeFieldRef, public TypeField {
public:
	TypeFieldRef(
			const std::string		&name,
			IDataType				*type,
			TypeFieldAttr			attr);

	virtual ~TypeFieldRef();

	virtual void accept(IVisitor *v) override { v->visitTypeFieldRef(this); }

};

}
} /* namespace vsc */

