
#pragma once
#include "vsc/IModelFieldFactory.h"
#include "vsc/IModelBuildContext.h"
#include "vsc/ITypeField.h"
#include "vsc/impl/TaskIsTypeFieldRef.h"
#include "vsc/impl/TaskBuildModelFieldConstraints.h"

namespace vsc {

class ModelFieldFactoryStruct : public virtual IModelFieldFactory {
public:

    virtual IModelField *createRootField(
        IModelBuildContext  *ctxt,
        IDataType           *type,
        const std::string   &name,
        bool                is_ref) override {
        IModelField *ret;

        if (is_ref) {
            ret = ctxt->ctxt()->mkModelFieldRefRoot(type, name);
        } else {
            ret = ctxt->ctxt()->mkModelFieldRoot(type, name);
        }

        IDataTypeStruct *type_s = dynamic_cast<IDataTypeStruct *>(type);
        // Push the new field just for completeness
        ctxt->pushField(ret);
        for (std::vector<ITypeFieldUP>::const_iterator 
            it=type_s->getFields().begin();
            it!=type_s->getFields().end(); it++) {
            IModelField *field = (*it)->getDataType()->getFactory()->createTypeField(
                ctxt,
                it->get());
        }
        ctxt->popField();

        // Finally, build out constraints on this field and sub-fields
        TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
        constraint_builder.build(ret, type);

        return ret;
    }

    virtual IModelField *createTypeField(
        IModelBuildContext  *ctxt,
        ITypeField          *type) override {
        IModelField *ret;

        if (TaskIsTypeFieldRef().eval(type)) {
            ret = ctxt->ctxt()->mkModelFieldRefType(type);
        } else {
            ret = ctxt->ctxt()->mkModelFieldType(type);
        }

        IDataTypeStruct *type_s = dynamic_cast<IDataTypeStruct *>(type);
        // Push the new field just for completeness
        ctxt->pushField(ret);
        for (std::vector<ITypeFieldUP>::const_iterator 
            it=type_s->getFields().begin();
            it!=type_s->getFields().end(); it++) {
            IModelField *field = (*it)->getDataType()->getFactory()->createTypeField(
                ctxt,
                it->get());
        }
        ctxt->popField();

        // Finally, build out constraints on this field and sub-fields
        TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
        constraint_builder.build(ret, type->getDataType());

        return ret;
    }
};

}