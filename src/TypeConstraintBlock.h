/*
 * TypeConstraintBlock.h
 *
 *  Created on: Apr 8, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeConstraintBlock.h"

namespace vsc {
namespace dm {

class TypeConstraintBlock : public ITypeConstraintBlock {
public:
	TypeConstraintBlock(const std::string &name);

	virtual ~TypeConstraintBlock();

	virtual const std::string &name() const override {
		return m_name;
	}

	virtual void addConstraint(ITypeConstraint *c) override;

	virtual const std::vector<ITypeConstraintUP> &constraints() const override {
		return m_constraints;
	}

	virtual void accept(IVisitor *v) override { v->visitTypeConstraintBlock(this); }

private:
	std::string							m_name;
	std::vector<ITypeConstraintUP>		m_constraints;
};

}
} /* namespace vsc */

