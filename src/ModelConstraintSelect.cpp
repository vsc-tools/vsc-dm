
#include "ModelConstraintSelect.h"

namespace vsc {

ModelConstraintSelect::ModelConstraintSelect(
    IContext        *ctxt,
    IModelField     *lhs) : m_lhs(lhs)  {

    IDataTypeInt *ui32_t = ctxt->findDataTypeInt(false, 32);
    if (!ui32_t) {
        ui32_t = ctxt->mkDataTypeInt(false, 32);
        ctxt->addDataTypeInt(ui32_t);
    }

    m_selector = IModelFieldUP(ctxt->mkModelFieldRoot(
        ui32_t,
        "selector"));
}

ModelConstraintSelect::~ModelConstraintSelect() {

}

void ModelConstraintSelect::addRhs(IModelField *rhs) {
    m_rhs.push_back(rhs);
}

}