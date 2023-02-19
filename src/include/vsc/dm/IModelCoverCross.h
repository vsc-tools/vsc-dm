
#pragma once
#include <memory>
#include <vector>
#include "vsc/dm/IAccept.h"
#include "vsc/dm/IModelCoverItem.h"
#include "vsc/dm/IModelCoverpoint.h"

namespace vsc {
namespace dm {

class IModelCovergroup;

class IModelCoverCross;
using IModelCoverCrossUP=UP<IModelCoverCross>;
class IModelCoverCross : public virtual IModelCoverItem {
public:

    virtual ~IModelCoverCross() { }

	virtual void setCovergroup(IModelCovergroup *cg) = 0;

	virtual IModelCovergroup *getCovergroup() const = 0;

	virtual const std::vector<IModelCoverpoint *> &coverpoints() const = 0;

	virtual void addCoverpoint(IModelCoverpoint *cp) = 0;

	virtual uint32_t getNumBins() const = 0;

	virtual std::string getBinName(int32_t bin_idx) = 0;

	virtual int32_t getBinHits(int32_t bin_idx) = 0;

};

}
}
