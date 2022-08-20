

#pragma once
#include <memory>
#include <string>

namespace vsc {

class IDataType;
class IModelBuildContext;
class IModelField;
class ITypeField;

class IModelFieldFactory;
using IModelFieldFactoryUP=std::unique_ptr<IModelFieldFactory>;
class IModelFieldFactory {
public:

    virtual ~IModelFieldFactory() { }

    virtual IModelField *createRootField(
        IModelBuildContext  *ctxt,
        IDataType           *type,
        const std::string   &name,
        bool                is_ref) = 0;

    virtual IModelField *createTypeField(
        IModelBuildContext  *ctxt,
        ITypeField          *type) = 0;

};

}