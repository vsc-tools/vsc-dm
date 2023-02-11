
#include "TypeConstraintIfElse.h"

namespace vsc {
namespace dm {

TypeConstraintIfElse::TypeConstraintIfElse(
    ITypeExpr           *cond,
    bool                cond_owned,
    ITypeConstraint     *true_c,
    bool                true_owned,
    ITypeConstraint     *false_c,
    bool                false_owned) : 
        m_cond(cond, cond_owned), 
        m_true(true_c, true_owned), 
        m_false(false_c, false_owned) {

}

TypeConstraintIfElse::~TypeConstraintIfElse() {

}

}
}

