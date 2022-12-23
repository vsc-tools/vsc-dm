
#pragma once
#include "vsc/dm/ITypeConstraintForeach.h"
#include "TypeConstraintScope.h"

namespace vsc {
namespace dm {

class TypeConstraintForeach : 
    public virtual ITypeConstraintForeach, 
    public virtual TypeConstraintScope {
public:

    TypeConstraintForeach(ITypeExpr *target);

    virtual ~TypeConstraintForeach();

    virtual ITypeExpr *getTarget() const override {
        return m_target.get();
    }

private:
    ITypeExprUP             m_target;

};

}
}

