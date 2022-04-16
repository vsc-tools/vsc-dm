/*
 * TypeExprFieldRef.h
 *
 *  Created on: Apr 7, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeExprFieldRef.h"

namespace vsc {

class TypeExprFieldRef : public ITypeExprFieldRef {
public:
	TypeExprFieldRef();

	virtual ~TypeExprFieldRef();

	virtual void addIdxRef(int32_t idx) override;

	virtual void addRootRef() override;

	virtual uint32_t size() const override { return m_path.size(); }

	virtual const TypeExprFieldRefElem &at(int32_t idx) const override {
		return m_path.at(idx);
	}

	virtual const std::vector<TypeExprFieldRefElem> &getPath() const override {
		return m_path;
	}

	virtual void accept(IVisitor *v) override { v->visitTypeExprFieldRef(this); }

private:
	std::vector<TypeExprFieldRefElem>					m_path;
};

} /* namespace vsc */

