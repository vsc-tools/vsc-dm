
#pragma once
#include "vsc/IModelCoverBinMask.h"
#include "vsc/IModelVal.h"
#include "ModelCoverBin.h"
#include "ModelVal.h"

namespace vsc {

class ModelCoverBinMask : 
    public virtual IModelCoverBinMask,
    public virtual ModelCoverBin {
public:

    ModelCoverBinMask(
        const std::string   &name,
        ModelCoverBinType   type,
        IModelVal           *value,
        IModelVal           *mask);

    virtual ~ModelCoverBinMask();

    virtual int32_t finalize(int32_t bin_idx_base) override;

    virtual void sample() override;

	virtual std::string getBinName(int32_t bin_idx) override {
        return name();
    }

    virtual int32_t getBinHits(int32_t bin_idx) override {
        return m_count;
    }

    virtual void accept(IVisitor *v) override { v->visitModelCoverBinMask(this); }

private:
    int32_t                    m_count;
	ModelVal			       m_tmpval;
    ModelVal                   m_value;
    ModelVal                   m_mask;

};

}