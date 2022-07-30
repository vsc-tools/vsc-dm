
#pragma once
#include <memory>
#include <vector>
#include "vsc/IAccept.h"
#include "vsc/IModelCoverItem.h"
#include "vsc/IModelCoverpoint.h"

namespace vsc {

class IModelCoverCross;
using IModelCoverCrossUP=std::unique_ptr<IModelCoverCross>;
class IModelCoverCross : public virtual IModelCoverItem {
public:

    virtual ~IModelCoverCross() { }

	virtual const std::vector<IModelCoverpoint *> &coverpoints() const = 0;

	virtual void addCoverpoint(IModelCoverpoint *cp) = 0;

	virtual uint32_t getNumBins() const = 0;

	virtual std::string getBinName(int32_t bin_idx) = 0;

};

}
