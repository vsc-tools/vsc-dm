
#pragma once
#include <memory>

namespace vsc {

class IModelCoverpointIff;
using IModelCoverpointIffUP=std::unique_ptr<IModelCoverpointIff>;
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
