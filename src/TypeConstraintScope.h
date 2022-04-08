/*
 * TypeConstraintScope.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeConstraintScope.h"

namespace vsc {

class TypeConstraintScope : public ITypeConstraintScope {
public:
	TypeConstraintScope();

	virtual ~TypeConstraintScope();

	virtual void addConstraint(ITypeConstraint *c) override;

	virtual const std::vector<ITypeConstraintUP> &constraints() const override {
		return m_constraints;
	}

	virtual void accept(IVisitor *v) override { /* TODO */ }

private:
	std::vector<ITypeConstraintUP>			m_constraints;
};

} /* namespace vsc */

