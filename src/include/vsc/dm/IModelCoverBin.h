
#pragma once
#include <memory>
#include <string>
#include "vsc/dm/IAccept.h"

namespace vsc {
namespace dm {

enum class ModelCoverBinType {
    Bins,
    IgnoreBins,
    IllegalBins
};

class IModelCoverpoint;

class IModelCoverBin;
using IModelCoverBinUP=UP<IModelCoverBin>;
class IModelCoverBin : public virtual IAccept {
public:

    virtual ~IModelCoverBin() { }

	virtual const std::string &name() const = 0;

    virtual ModelCoverBinType getType() const = 0;

    virtual void setCoverpoint(IModelCoverpoint *cp) = 0;

    virtual IModelCoverpoint *getCoverpoint() const = 0;

    /**
     * @brief Finalizes configuration for this bin
     * 
     * @param bin_idx_base - Base index for bins
     * @return int32_t - total number of bins
     */
    virtual int32_t finalize(int32_t bin_idx_base) = 0;

    virtual void sample() = 0;

    virtual int32_t getNumBins() const = 0;

	virtual std::string getBinName(int32_t bin_idx) = 0;

    virtual int32_t getBinHits(int32_t bin_idx) = 0;

};

}
}
