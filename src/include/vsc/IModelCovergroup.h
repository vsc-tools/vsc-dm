
#pragma once
#include <memory>
#include <vector>
#include "vsc/IAccept.h"
#include "vsc/IModelCoverItem.h"
#include "vsc/IModelCoverpoint.h"
#include "vsc/IModelCoverCross.h"

namespace vsc {

class IModelCovergroup;
using IModelCovergroupUP=std::unique_ptr<IModelCovergroup>;
class IModelCovergroup : public virtual IModelCoverItem {
public:

    virtual ~IModelCovergroup() { }

    virtual void addCoverpoint(IModelCoverpoint *cp) = 0;

    virtual const std::vector<IModelCoverpointUP> &coverpoints() const = 0;

    virtual void addCross(IModelCoverCross *cross) = 0;

    virtual const std::vector<IModelCoverCrossUP> &crosses() const = 0;

    /**
     * Used by coverpoints to notify the covergroup of a 
     * change in achieved coverage
     */
    virtual void coverageEvent() = 0;



};

}