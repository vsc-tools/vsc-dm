
#include "ModelExprIndexedFieldRef.h"

namespace vsc {

ModelExprIndexedFieldRef::ModelExprIndexedFieldRef() {

}

ModelExprIndexedFieldRef::~ModelExprIndexedFieldRef() {

}

void ModelExprIndexedFieldRef::addFieldRef(IModelExprFieldRef *off_e) {
    m_path.push_back(ModelExprIndexedFieldRefElem{
        ModelExprIndexedFieldRefKind::Field,
        IModelExprUP(off_e)
    });
}

void ModelExprIndexedFieldRef::addFieldIndexRef(IModelExpr *off_e) {
    m_path.push_back(ModelExprIndexedFieldRefElem{
        ModelExprIndexedFieldRefKind::FieldIndex,
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