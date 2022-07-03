/*
 * ModelFieldVec.h
 *
 *  Created on: Nov 7, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/IContext.h"
#include "vsc/IModelFieldVec.h"
#include "ModelField.h"

namespace vsc {

class ModelFieldVec : public virtual IModelFieldVec, public virtual ModelField {
public:
	ModelFieldVec(IContext *ctxt);

	virtual ~ModelFieldVec();

	virtual IModelField *getSizeRef() const override { return m_size.get(); }

	virtual uint32_t getSize() const override { return m_fields.size(); }

	virtual void push_back(IModelField *f) override;

	virtual IModelField *at(uint32_t idx) override;

	virtual void pop_back() override;

	virtual IModelFieldFactory *getFieldFactory() override {
		return m_factory.get();
	}

	virtual void setFieldFactory(IModelFieldFactory *f) override {
		m_factory = IModelFieldFactoryUP(f);
	}

protected:
	IModelFieldUP					m_size;
	IModelFieldFactoryUP			m_factory;

};

} /* namespace vsc */

