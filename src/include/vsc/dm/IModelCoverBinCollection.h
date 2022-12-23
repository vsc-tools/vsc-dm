
#pragma once
#include "vsc/dm/IModelCoverBin.h"

namespace vsc {
namespace dm {

class IModelCoverBinCollection : public virtual IModelCoverBin {
public:

    virtual ~IModelCoverBinCollection() { }

    virtual void addBin(IModelCoverBin *bin) = 0;

};

}
}
