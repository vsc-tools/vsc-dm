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

	virtual const std::vector<ITypeConstraint *> &getConstraints() const override {
		return m_constraints;
	}

	virtual void accept(IVisitor *v) override { v->visitTypeConstraintScope(this); }

private:
	std::vector<ITypeConstraint *>			m_constraints;
    std::vector<IAcceptUP>                  m_owned;
};

}
} /* namespace vsc */

