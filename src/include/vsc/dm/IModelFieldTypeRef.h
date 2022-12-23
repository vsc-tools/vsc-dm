
#pragma once
#include "vsc/dm/IModelFieldRef.h"

namespace vsc {
namespace dm {

class IModelFieldTypeRef : public virtual IModelFieldRef {
public:

    virtual ~IModelFieldTypeRef() { }

	virtual ITypeField *getTypeField() const = 0;

	template <class T> T *getTypeFieldT() const {
		return dynamic_cast<T *>(getTypeField());
	}

    virtual IDataType *getDataTypeRef() const = 0;

};

}
}
