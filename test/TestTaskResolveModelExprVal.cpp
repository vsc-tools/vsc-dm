
#include "TestTaskResolveModelExprVal.h"
#include "vsc/impl/TaskResolveModelExprVal.h"
#include "Context.h"

namespace vsc {

TEST_F(TestTaskResolveModelExprVal, smoke) {
    Context ctx;

    IDataTypeInt *vsc_uint32_t = ctx.mkDataTypeInt(false, 32);
    ctx.addDataTypeInt(vsc_uint32_t);

    IModelField *a = ctx.mkModelFieldRoot(vsc_uint32_t, "a");
    a->val()->set_val_u(1);

    IModelVal *val_1 = ctx.mkModelVal();
    val_1->set_val_u(1, 15);
    IModelExprUP true_e(ctx.mkModelExprBin(
        ctx.mkModelExprFieldRef(a),
        BinOp::Eq,
        ctx.mkModelExprVal(val_1)
    ));

    IModelVal *val_7 = ctx.mkModelVal();
    val_7->set_val_u(7, 15);
    IModelExprUP false_e(ctx.mkModelExprBin(
        ctx.mkModelExprFieldRef(a),
        BinOp::Eq,
        ctx.mkModelExprVal(val_7)
    ));

    IModelValUP res_1(ctx.mkModelVal());
    TaskResolveModelExprVal(&ctx).eval(
        res_1.get(),
        true_e.get());
    ASSERT_EQ(res_1->val_u(), 1);

    IModelValUP res_2(ctx.mkModelVal());
    TaskResolveModelExprVal(&ctx).eval(
        res_2.get(),
        false_e.get());
    ASSERT_EQ(res_2->val_u(), 0);
}

}