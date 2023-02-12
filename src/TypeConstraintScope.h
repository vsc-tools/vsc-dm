/*
 * TypeConstraintScope.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeConstraintScope.h"

namespace vsc {
namespace dm {

class TypeConstraintScope : public ITypeConstraintScope {
public:
	TypeConstraintScope();

	virtual ~TypeConstraintScope();

	virtual void addConstraint(
        ITypeConstraint         *c,
        bool                    owned) override;

	virtual const std::vector<ITypeConstraintUP> &getConstraints() const override {
		return m_constraints;
	}

	virtual void accept(IVisitor *v) override { v->visitTypeConstraintScope(this); }

private:
	std::vector<ITypeConstraintUP>			m_constraints;
};

}
} /* namespace vsc */

