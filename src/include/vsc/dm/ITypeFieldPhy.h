/*
 * ITypeFieldPhy.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeField.h"

namespace vsc {
namespace dm {

class ITypeFieldPhy : public virtual ITypeField {
public:

	virtual ~ITypeFieldPhy() { }

	virtual IModelVal *getInit() const = 0;

};

}
}

