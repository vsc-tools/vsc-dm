/*
 * ModelExprFieldRef.h
 *
 *  Created on: Oct 4, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelExprFieldRef.h"
#include "ModelField.h"

namespace vsc {
namespace dm {

class ModelExprFieldRef : public IModelExprFieldRef {
public:
	ModelExprFieldRef(IModelField *field);

	virtual ~ModelExprFieldRef();

	virtual int32_t width() override {
        // TODO:
        return -1;
//		return m_field->getDataType()->get()->bits();
	}

	virtual IModelField *field() const override { return m_field; }

	virtual void eval(IModelVal *dst) override;

	virtual void accept(IVisitor *v) { v->visitModelExprFieldRef(this); }

private:
	IModelField					*m_field;

};

}
} /* namespace vsc */

