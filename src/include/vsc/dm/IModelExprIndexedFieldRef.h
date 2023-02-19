
#pragma once
#include <vector>
#include "vsc/dm/IModelExpr.h"
#include "vsc/dm/IModelExprFieldRef.h"

namespace vsc {
namespace dm {

enum class ModelExprIndexedFieldRefKind {
    Field,          // Value in the 'field' union entry
    FieldIndex,     // Field offset in the 'offset' entry
    VecIndex        // 
};

struct ModelExprIndexedFieldRefElem {
    virtual ~ModelExprIndexedFieldRefElem() {
        if (kind == ModelExprIndexedFieldRefKind::VecIndex && idx_e) {
            delete idx_e;
        }
    }

    ModelExprIndexedFieldRefKind    kind;
    union {
        IModelExpr                      *idx_e;
        IModelField                     *field;
        int32_t                         offset;
    };
};

class IModelExprIndexedFieldRef;
using IModelExprIndexedFieldRefUP=UP<IModelExprIndexedFieldRef>;
class IModelExprIndexedFieldRef : public virtual IModelExpr {
public:

    virtual ~IModelExprIndexedFieldRef() { }

    virtual void addField(IModelField *field) = 0;

    virtual void addFieldOffsetRef(int32_t offset) = 0;

    virtual void addVecIndexRef(IModelExpr *idx_e) = 0;

    virtual uint32_t size() const = 0;

    virtual const ModelExprIndexedFieldRefElem &at(int32_t idx) const = 0;

    virtual const std::vector<ModelExprIndexedFieldRefElem> &getPath() const = 0;

};

}
}
