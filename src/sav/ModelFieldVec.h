/*
 * ModelFieldVec.h
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IContext.h"
#include "vsc/dm/IModelFieldVec.h"
#include "ModelField.h"

namespace vsc {
namespace dm {

class ModelFieldVec : public virtual IModelFieldVec, public virtual ModelField {
public:
	ModelFieldVec(IContext *ctxt);

	virtual ~ModelFieldVec();

	virtual IModelField *getSizeRef() const override { return m_size.get(); }

	virtual uint32_t getSize() const override { return m_fields.size(); }

	virtual void push_back(IModelField *f) override;

	virtual IModelField *at(uint32_t idx) override;

	virtual void pop_back() override;

	virtual IModelFieldVecElemFactory *getElemFactory() override {
		return m_factory.get();
	}

	virtual void setElemFactory(IModelFieldVecElemFactory *f) override {
		m_factory = IModelFieldVecElemFactoryUP(f);
	}

protected:
	IModelFieldUP					m_size;
	IModelFieldVecElemFactoryUP		m_factory;

};

}
} /* namespace vsc */

