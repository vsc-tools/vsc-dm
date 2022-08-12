
#include "TypeConstraintUnique.h"

namespace vsc {

TypeConstraintUnique::TypeConstraintUnique(const std::vector<ITypeExpr *> &exprs) {

    for (std::vector<ITypeExpr *>::const_iterator
        it=exprs.begin();
        it!=exprs.end();
        it++) {
        m_exprs.push_back(ITypeExprUP(*it));
    }
}

TypeConstraintUnique::~TypeConstraintUnique() {

}

}
