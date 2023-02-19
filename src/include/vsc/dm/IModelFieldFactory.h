

#pragma once
#include <memory>
#include <string>

namespace vsc {
namespace dm {

class IDataType;
class IModelBuildContext;
class IModelField;
class ITypeField;

class IModelFieldFactory;
using IModelFieldFactoryUP=UP<IModelFieldFactory>;
class IModelFieldFactory {
public:

    virtual ~IModelFieldFactory() { }

    virtual IModelField *createRootField(
        IModelBuildContext  *ctxt,
        IDataType           *type,
        const std::string   &name,
        bool                is_ref) = 0;

    template <class T> T *createRootFieldT(
        IModelBuildContext  *ctxt,
        IDataType           *type,
        const std::string   &name,
        bool                is_ref) {
        return dynamic_cast<T *>(createRootField(ctxt, type, name, is_ref));
    }

    virtual IModelField *createTypeField(
        IModelBuildContext  *ctxt,
        ITypeField          *type) = 0;

    template <class T> T *createTypeFieldT(
        IModelBuildContext  *ctxt,
        ITypeField          *type) {
        return dynamic_cast<T *>(createTypeField(ctxt, type));
    }

};

}
}
