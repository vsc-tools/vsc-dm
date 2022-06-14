/*
 * ModelBuildContext.h
 *
 *  Created on: Jun 12, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/IModelBuildContext.h"

namespace vsc {

class ModelBuildContext : public virtual IModelBuildContext {
public:

	ModelBuildContext(IContext *ctxt) : m_ctxt(ctxt) { }

	virtual ~ModelBuildContext() { }

	virtual IContext *ctxt() const override { return m_ctxt; }

	virtual void pushField(IModelField *f) override {
		m_field_s.push_back(f);
	}

	virtual void popField() override {
		m_field_s.pop_back();
	}

	virtual IModelField *getField(int32_t offset=0) override {
		return m_field_s.at(m_field_s.size()-offset-1);
	}

protected:
	IContext							*m_ctxt;
	std::vector<IModelField *>			m_field_s;

};

}
