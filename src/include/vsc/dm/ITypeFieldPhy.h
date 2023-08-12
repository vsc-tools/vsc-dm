/*
 * ITypeFieldPhy.h
 *
 *  Created on: May 10, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeField.h"
#include "vsc/dm/Val.h"

namespace vsc {
namespace dm {

class ITypeFieldPhy : public virtual ITypeField {
public:

	virtual ~ITypeFieldPhy() { }

    virtual bool haveInit() const = 0;

	virtual ValData getInit() const = 0;

};

}
}

