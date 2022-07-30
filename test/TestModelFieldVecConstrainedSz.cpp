
#include "TestModelFieldVecConstrainedSz.h"
#include "vsc/ICompoundSolver.h"
#include "vsc/IModelFieldVec.h"
#include "Context.h"


namespace vsc {

TEST_F(TestModelFieldVecConstrainedSz, scalar_fixed_sz_reduce_sz) {
    Context ctx;
    IDataTypeInt *vsc_uint32_t = ctx.mkDataTypeInt(false, 32);
    ctx.addDataTypeInt(vsc_uint32_t);

    IModelFieldVecUP vec(ctx.mkModelFieldVecRoot(vsc_uint32_t, "vec"));
    vec->setFlag(ModelFieldFlag::DeclRand|ModelFieldFlag::UsedRand);

    // Add a baseline of 20 fields
    for (uint32_t i=0; i<20; i++) {
        char tmp[16];
        sprintf(tmp, "[%d]", i);
        IModelFieldRoot *f = ctx.mkModelFieldRoot(vsc_uint32_t, tmp);
        vec->addField(f);
    }

    IModelVal *val = ctx.mkModelVal();
    val->set_val_u(10, 32);
    IModelConstraintExprUP constraint(ctx.mkModelConstraintExpr(
        ctx.mkModelExprBin(
            ctx.mkModelExprFieldRef(vec->getSizeRef()),
            BinOp::Eq,
            ctx.mkModelExprVal(val))
    ));

    IRandStateUP rs(ctx.mkRandState("0"));
    ICompoundSolverUP solver(ctx.mkCompoundSolver());
    for (uint32_t i=0; i<4; i++) {
        char tmp[16];
        solver->solve(
            rs.get(),
            {vec.get()},
            {constraint.get()},
            SolveFlags::RandomizeTopFields);

        ASSERT_EQ(vec->getSize(), 10);
        ASSERT_EQ(vec->getSizeRef()->val()->val_u(), 10);

        sprintf(tmp, "[%d]", 4+i);
        IModelFieldRoot *f = ctx.mkModelFieldRoot(vsc_uint32_t, tmp);
        vec->addField(f);
    }
}

}