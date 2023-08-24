/*
 * ModelExprVal.h
 *
 *  Created on: Oct 30, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExprVal.h"
#include "ModelVal.h"

namespace vsc {
namespace dm {

class ModelExprVal : public IModelExprVal {
public:
	ModelExprVal();

	ModelExprVal(const IModelVal *val);

	ModelExprVal(const IModelVal &val);

	virtual ~ModelExprVal();

	virtual int32_t width() override { 
        // TODO:
        return -1;
    }

    virtual ValRef getVal() const override { return m_val; }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) override { v->visitModelExprVal(this); }

private:
    ValRef              m_val;
};

}
} /* namespace vsc */

