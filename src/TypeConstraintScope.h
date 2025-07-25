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

class TypeConstraintScope : 
    public virtual ITypeConstraintScope {
public:
	TypeConstraintScope();

	virtual ~TypeConstraintScope();

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

    virtual void setAssociatedData(IAssociatedData *data, bool owned=true) override {
        m_assoc_data = IAssociatedDataUP(data, owned);
    }

    virtual IAssociatedData *getAssociatedData() const override {
        return m_assoc_data.get();
    }

	virtual void accept(IVisitor *v) override { v->visitTypeConstraintScope(this); }

private:
    static std::vector<ITypeVarUP>          m_null;
	std::vector<ITypeConstraintUP>			m_constraints;
    IAssociatedDataUP                       m_assoc_data;
};

}
} /* namespace vsc */

