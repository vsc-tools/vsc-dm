
#include "ModelConstraintUnique.h"

namespace vsc {

ModelConstraintUnique::ModelConstraintUnique(const std::vector<IModelExpr *> &exprs) {
    for (std::vector<IModelExpr *>::const_iterator
        it=exprs.begin();
        it!=exprs.end(); it++) {
        m_exprs.push_back(IModelExprUP(*it));
    }
}

ModelConstraintUnique::~ModelConstraintUnique() {

}

}