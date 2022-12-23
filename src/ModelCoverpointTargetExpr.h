
#pragma once
#include "vsc/dm/IModelCoverpointTarget.h"
#include "vsc/dm/IModelExpr.h"
#include "vsc/dm/impl/TaskResolveModelExprVal.h"

namespace vsc {
namespace dm {

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
}
