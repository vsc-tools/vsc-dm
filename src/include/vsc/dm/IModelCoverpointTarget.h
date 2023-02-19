
#pragma once
#include <memory>
#include "vsc/dm/IModelVal.h"

namespace vsc {
namespace dm {

class IModelCoverpointTarget;
using IModelCoverpointTargetUP=UP<IModelCoverpointTarget>;
class IModelCoverpointTarget {
public:

    virtual ~IModelCoverpointTarget() { }

    /**
     * @brief Obtain the current value of the coverpoint target
     * 
     * @param val 
     */
    virtual void getValue(IModelVal *val) = 0;

};

}
}
