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

class TypeConstraintBlock : 
    public virtual ITypeConstraintBlock {
public:
	TypeConstraintBlock(const std::string &name);

	virtual ~TypeConstraintBlock();

	virtual const std::string &name() const override {
		return m_name;
	}

	virtual void addConstraint(
        ITypeConstraint         *c,
        bool                    owned) override;

	virtual const std::vector<ITypeConstraintUP> &getConstraints() const override {
		return m_constraints;
	}

    virtual int32_t addVariable(ITypeVar *var, bool owned=true) override {
        return -1;
    }

    virtual int32_t getNumVariables() override { return 0; }

    virtual const std::vector<ITypeVarUP> &getVariables() const override {
        return m_null;
    }

	virtual void accept(IVisitor *v) override { v->visitTypeConstraintBlock(this); }

private:
    static std::vector<ITypeVarUP>          m_null;
	std::string							m_name;
	std::vector<ITypeConstraintUP>		m_constraints;
};

}
} /* namespace vsc */

