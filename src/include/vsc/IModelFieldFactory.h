

#pragma once
#include <memory>
#include <string>

namespace vsc {

class IModelBuildContext;
class IModelField;

class IModelFieldFactory;
using IModelFieldFactoryUP=std::unique_ptr<IModelFieldFactory>;
class IModelFieldFactory {
public:

    virtual ~IModelFieldFactory() { }

    virtual IModelField *create(
        IModelBuildContext  *ctxt,
        IDataType           *type,
        const std::string   &name) = 0;

};

}