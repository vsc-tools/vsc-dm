
#pragma once
#include "vsc/IModelCoverBin.h"

namespace vsc {

class IModelCoverBinCollection : public virtual IModelCoverBin {
public:

    virtual ~IModelCoverBinCollection() { }

    virtual void addBin(IModelCoverBin *bin) = 0;

};

}