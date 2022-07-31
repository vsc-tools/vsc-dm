
#pragma once
#include "vsc/IModelCoverpointTarget.h"
#include "vsc/IModelExpr.h"
#include "vsc/impl/TaskResolveModelExprVal.h"

namespace vsc {

class ModelCoverpointTargetExpr : public virtual IModelCoverpointTarget {
public:

    ModelCoverpointTargetExpr(
        IContext            *ctxt,
        IModelExpr          *expr,
        int32_t             width);

    virtual ~ModelCoverpointTargetExpr();

    virtual void getValue(IModelVal *val) override;

private:
    IModelExprUP                m_expr;
    TaskResolveModelExprVal     m_resolver;
    int32_t                     m_width;

};

}