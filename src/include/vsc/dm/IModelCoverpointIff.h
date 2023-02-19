
#pragma once
#include <memory>

namespace vsc {
namespace dm {

class IModelCoverpointIff;
using IModelCoverpointIffUP=UP<IModelCoverpointIff>;
class IModelCoverpointIff { 
public:

    virtual ~IModelCoverpointIff() { }

    /**
     * @brief Compute the 'iff' expression
     * 
     * @return true 
     * @return false 
     */
    virtual bool getIff() = 0;

};

}
}
