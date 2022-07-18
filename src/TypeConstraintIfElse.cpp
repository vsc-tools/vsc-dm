
#include "TypeConstraintIfElse.h"

namespace vsc {

TypeConstraintIfElse::TypeConstraintIfElse(
    ITypeExpr           *cond,
    ITypeConstraint     *true_c,
    ITypeConstraint     *false_c) : m_cond(cond), m_true(true_c), m_false(false_c) {

}

TypeConstraintIfElse::~TypeConstraintIfElse() {

}

}