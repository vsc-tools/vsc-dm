
#pragma once
#include "vsc/dm/IDataType.h"

namespace vsc {
namespace dm {

class IDataTypeTypeRef : public virtual IDataType {
public:

    virtual ~IDataTypeTypeRef() { }

    virtual IDataType *getDataTypeRef() const = 0;

};

}
}
