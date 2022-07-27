
#pragma once
#include <vector>
#include "vsc/IModelExpr.h"
#include "vsc/IModelExprFieldRef.h"

namespace vsc {

enum class ModelExprIndexedFieldRefKind {
    Field,
    FieldIndex,
    VecIndex
};

struct ModelExprIndexedFieldRefElem {
    ModelExprIndexedFieldRefKind    kind;
    IModelExprUP                    idx_e;
};

class IModelExprIndexedFieldRef;
using IModelExprIndexedFieldRefUP=std::unique_ptr<IModelExprIndexedFieldRef>;
class IModelExprIndexedFieldRef : public virtual IModelExpr {
public:

    virtual ~IModelExprIndexedFieldRef() { }

    virtual void addFieldRef(IModelExprFieldRef *ref) = 0;

    virtual void addFieldIndexRef(IModelExpr *off_e) = 0;

    virtual void addVecIndexRef(IModelExpr *idx_e) = 0;

    virtual uint32_t size() const = 0;

    virtual const ModelExprIndexedFieldRefElem &at(int32_t idx) const = 0;

    virtual const std::vector<ModelExprIndexedFieldRefElem> &getPath() const = 0;

};

}