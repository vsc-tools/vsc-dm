
#include "vsc/dm/IModelCoverpoint.h"
#include "ModelCoverBinMask.h"
#include "ModelValOp.h"

namespace vsc {
namespace dm {

ModelCoverBinMask::ModelCoverBinMask(
    const std::string               &name,
    ModelCoverBinType               type,
    IModelVal                       *value,
    IModelVal                       *mask) :
        ModelCoverBin(name, type, false),
        m_value(value), m_mask(mask) {
    m_count = 0;
    m_tmpval.setBits(m_value.bits());
}

ModelCoverBinMask::~ModelCoverBinMask() {

}

int32_t ModelCoverBinMask::finalize(int32_t bin_idx_base) {
    m_n_bins = 1;
    m_bin_idx_base = bin_idx_base;
    return m_n_bins;
}

void ModelCoverBinMask::sample() {
    const IModelVal *val = getCoverpoint()->getVal();

    ModelValOp::bin_and_s(&m_tmpval, val, &m_mask);
    if (ModelValOp::eq_s(&m_tmpval, &m_value)) {
        m_count++;
        m_cp->coverageEvent(m_type, m_bin_idx_base);
    }
}

}
}
