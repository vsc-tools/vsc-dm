
#include "ModelExprIndexedFieldRef.h"

namespace vsc {

ModelExprIndexedFieldRef::ModelExprIndexedFieldRef() {

}

ModelExprIndexedFieldRef::~ModelExprIndexedFieldRef() {

}

void ModelExprIndexedFieldRef::addActiveScopeRef(IModelExpr *off_e) {
    m_path.push_back(ModelExprIndexedFieldRefElem{
        ModelExprIndexedFieldRefKind::ActiveScope,
        IModelExprUP(off_e)
    });
}

void ModelExprIndexedFieldRef::addVecIndexRef(IModelExpr *idx_e) {
    m_path.push_back(ModelExprIndexedFieldRefElem{
        ModelExprIndexedFieldRefKind::VecIndex,
        IModelExprUP(idx_e)
    });
}

}