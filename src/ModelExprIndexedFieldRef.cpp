
#include "ModelExprIndexedFieldRef.h"
#include "vsc/dm/IModelField.h"

namespace vsc {
namespace dm {

ModelExprIndexedFieldRef::ModelExprIndexedFieldRef() : m_width(-1) {

}

ModelExprIndexedFieldRef::~ModelExprIndexedFieldRef() {

}

int32_t ModelExprIndexedFieldRef::width() {
    if (m_width == -1) {
        IModelField *f = 0;
        for (std::vector<ModelExprIndexedFieldRefElem>::const_iterator
            it=m_path.begin();
            it!=m_path.end(); it++) {
            switch (it->kind) {
                case ModelExprIndexedFieldRefKind::Field: {
                    f = it->field;
                    if (f && f->val()) {
                        m_width = f->val()->bits();
                    }
                } break;
                case ModelExprIndexedFieldRefKind::FieldIndex: {
                    f = f->getField(it->offset);
                    if (f) {
                        m_width = f->val()->bits();
                    }
                }
            }
        }
    }
    return m_width;
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
}
