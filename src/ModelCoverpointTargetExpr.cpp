
#include "ModelCoverpointTargetExpr.h"

namespace vsc {
namespace dm {

ModelCoverpointTargetExpr::ModelCoverpointTargetExpr(
        IContext    *ctxt,
        IModelExpr  *expr,
        int32_t     width) : m_expr(expr), m_resolver(ctxt), m_width(width) {

}

ModelCoverpointTargetExpr::~ModelCoverpointTargetExpr() {

}

void ModelCoverpointTargetExpr::getValue(IModelVal *val) {
//    m_resolver.eval(val, m_expr.get(), m_width);
}

}
}
