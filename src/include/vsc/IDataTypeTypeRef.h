
#pragma once
#include "vsc/IDataType.h"

namespace vsc {

class IDataTypeTypeRef : public virtual IDataType {
public:

    virtual ~IDataTypeTypeRef() { }

    virtual IDataType *getDataTypeRef() const = 0;

};

}