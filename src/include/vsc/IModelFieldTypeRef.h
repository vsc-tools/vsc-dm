
#pragma once
#include "vsc/IModelField.h"

namespace vsc {

class IModelFieldTypeRef : public virtual IModelField {
public:

    virtual ~IModelFieldTypeRef() { }


    virtual IDataType *getDataTypeRef() const = 0;

};

}