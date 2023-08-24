/*
 * IModelExprVal.h
 *
 *  Created on: Feb 11, 2022
 *      Author: mballance
 */
#pragma once
#include "vsc/dm/IModelExpr.h"
#include "vsc/dm/IModelVal.h"
#include "vsc/dm/impl/ValRef.h"

namespace vsc {
namespace dm {

class IModelExprVal : public IModelExpr {
public:

	virtual ~IModelExprVal() { }

    /**
     * @brief Returns an immutable ref to the value
     * 
     * @return ValRef 
     */
    virtual ValRef getVal() const = 0;

};

}
}
