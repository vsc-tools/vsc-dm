
#include "TestModelFieldVecUnconstraintedSz.h"
#include "vsc/ICompoundSolver.h"
#include "vsc/IModelFieldVec.h"
#include "Context.h"

namespace vsc {

TEST_F(TestModelFieldVecUnconstrainedSz, smoke) {
    Context ctx;
    IDataTypeInt *vsc_uint32_t = ctx.mkDataTypeInt(false, 32);
    ctx.addDataTypeInt(vsc_uint32_t);

    IModelFieldVecUP vec(ctx.mkModelFieldVecRoot(vsc_uint32_t, "vec"));
    vec->setFlag(ModelFieldFlag::DeclRand|ModelFieldFlag::UsedRand);

    // Add a baseline of 4 fields
    for (uint32_t i=0; i<4; i++) {
        char tmp[16];
        sprintf(tmp, "[%d]", i);
        IModelFieldRoot *f = ctx.mkModelFieldRoot(vsc_uint32_t, tmp);
        vec->addField(f);
    }

    IRandStateUP rs(ctx.mkRandState("0"));
    ICompoundSolverUP solver(ctx.mkCompoundSolver());
    for (uint32_t i=0; i<4; i++) {
        char tmp[16];
        solver->solve(
            rs.get(),
            {vec.get()},
            {},
            SolveFlags::RandomizeTopFields);

        ASSERT_EQ(vec->getSize(), 4+i);
        ASSERT_EQ(vec->getSizeRef()->val()->val_u(), 4+i);

        sprintf(tmp, "[%d]", 4+i);
        IModelFieldRoot *f = ctx.mkModelFieldRoot(vsc_uint32_t, tmp);
        vec->addField(f);
    }
}

TEST_F(TestModelFieldVecUnconstrainedSz, fixed_foreach) {
    Context ctx;
    IDataTypeInt *vsc_uint32_t = ctx.mkDataTypeInt(false, 32);
    ctx.addDataTypeInt(vsc_uint32_t);

    IModelFieldVec *vec = ctx.mkModelFieldVecRoot(vsc_uint32_t, "vec");
    vec->setFlag(ModelFieldFlag::DeclRand|ModelFieldFlag::UsedRand);
    IModelConstraintForeachUP constraint(ctx.mkModelConstraintForeach(
        ctx.mkModelExprFieldRef(vec),
        "i"));
    IModelExprIndexedFieldRef *vec_i = ctx.mkModelExprIndexedFieldRef();
    vec_i->addFieldRef(ctx.mkModelExprFieldRef(vec));
    vec_i->addVecIndexRef(ctx.mkModelExprFieldRef(constraint->getIndexIt()));
    constraint->addConstraint(ctx.mkModelConstraintExpr(
        ctx.mkModelExprBin(
            vec_i,
            BinOp::Eq,
            ctx.mkModelExprFieldRef(constraint->getIndexIt())
        )));

    // Add a baseline of 4 fields
    for (uint32_t i=0; i<4; i++) {
        char tmp[16];
        sprintf(tmp, "[%d]", i);
        IModelFieldRoot *f = ctx.mkModelFieldRoot(vsc_uint32_t, tmp);
        vec->addField(f);
    }

    IRandStateUP rs(ctx.mkRandState("0"));
    ICompoundSolverUP solver(ctx.mkCompoundSolver());
    for (uint32_t i=0; i<4; i++) {
        char tmp[16];
        solver->solve(
            rs.get(),
            {vec},
            {constraint.get()},
            SolveFlags::RandomizeTopFields);

        ASSERT_EQ(vec->getSize(), 4+i);
        ASSERT_EQ(vec->getSizeRef()->val()->val_u(), 4+i);

        // Now, check all the elements
        for (uint32_t j=0; j<vec->getSize(); j++) {
            ASSERT_EQ(vec->getField(j)->val()->val_u(), j);
        }

        sprintf(tmp, "[%d]", 4+i);
        IModelFieldRoot *f = ctx.mkModelFieldRoot(vsc_uint32_t, tmp);
        vec->addField(f);
    }
}

}