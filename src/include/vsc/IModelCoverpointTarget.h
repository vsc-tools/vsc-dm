
#pragma once
#include <memory>
#include "vsc/IModelVal.h"

namespace vsc {

class IModelCoverpointTarget;
using IModelCoverpointTargetUP=std::unique_ptr<IModelCoverpointTarget>;
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