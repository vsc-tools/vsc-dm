
#include "TypeConstraintImplies.h"

namespace vsc {
namespace dm {

TypeConstraintImplies::TypeConstraintImplies(
    ITypeExpr       *cond,
    ITypeConstraint *body,
    bool            cond_owned,
    bool            body_owned) : 
        m_cond(cond, cond_owned), m_body(body, body_owned) {

}

TypeConstraintImplies::~TypeConstraintImplies() {

}

}
}

