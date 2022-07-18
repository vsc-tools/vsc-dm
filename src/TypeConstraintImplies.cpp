
#include "TypeConstraintImplies.h"

namespace vsc {

TypeConstraintImplies::TypeConstraintImplies(
    ITypeExpr       *cond,
    ITypeConstraint *body) : m_cond(cond), m_body(body) {

}

TypeConstraintImplies::~TypeConstraintImplies() {

}

}