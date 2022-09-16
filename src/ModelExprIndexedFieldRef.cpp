
#include "ModelExprIndexedFieldRef.h"

namespace vsc {

ModelExprIndexedFieldRef::ModelExprIndexedFieldRef() {

}

ModelExprIndexedFieldRef::~ModelExprIndexedFieldRef() {

}

void ModelExprIndexedFieldRef::addField(IModelField *field) {
    ModelExprIndexedFieldRefElem ref_e;
    ref_e.kind = ModelExprIndexedFieldRefKind::Field;
    ref_e.field = field;
    m_path.push_back(ref_e);
}

void ModelExprIndexedFieldRef::addFieldOffsetRef(int32_t offset) {
    ModelExprIndexedFieldRefElem ref_e;
    ref_e.kind = ModelExprIndexedFieldRefKind::FieldIndex;
    ref_e.offset = offset;
    m_path.push_back(ref_e);
}

void ModelExprIndexedFieldRef::addVecIndexRef(IModelExpr *idx_e) {
    ModelExprIndexedFieldRefElem ref_e;
    ref_e.kind = ModelExprIndexedFieldRefKind::VecIndex;
    ref_e.idx_e = idx_e;
    m_path.push_back(ref_e);
}

}