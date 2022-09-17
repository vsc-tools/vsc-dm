
#pragma once
#include "vsc/IModelExprIndexedFieldRef.h"
#include "ModelExpr.h"

namespace vsc {

class ModelExprIndexedFieldRef : 
    public virtual IModelExprIndexedFieldRef,
    public virtual ModelExpr {
public:

    ModelExprIndexedFieldRef();

    virtual ~ModelExprIndexedFieldRef();

    virtual int32_t width() override;

	virtual void eval(IModelVal *dst) override { }

    virtual void addField(IModelField *field) override;

    virtual void addFieldOffsetRef(int32_t offset) override;

    virtual void addVecIndexRef(IModelExpr *idx_e) override;

    virtual uint32_t size() const override { return m_path.size(); }

    virtual const ModelExprIndexedFieldRefElem &at(int32_t idx) const override {
        return m_path.at(idx);
    }

    virtual const std::vector<ModelExprIndexedFieldRefElem> &getPath() const override {
        return m_path;
    }

    virtual void accept(IVisitor *v) override { v->visitModelExprIndexedFieldRef(this); }

private:
    int32_t                                         m_width;
    std::vector<ModelExprIndexedFieldRefElem>       m_path;

};

}
