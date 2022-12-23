
#include "TestModelCoverpoint.h"
#include "Context.h"

namespace vsc {
namespace dm {

TEST_F(TestModelCoverpoint, single_cp_single_bin) {
    Context ctx;

    IModelCovergroupUP cg(ctx.mkModelCovergroup("cg"));
    IModelValUP val(ctx.mkModelVal());
    IModelExprVal *val_e = ctx.mkModelExprVal(val.get());
    IModelCoverpoint *cp1 = ctx.mkModelCoverpoint(
        "cp1",
        ctx.mkModelCoverpointTargetExpr(val_e, 32),
        0);
    val->set_val_u(10, 32);
    cp1->addBin(ctx.mkModelCoverBinSingleVal("b", ModelCoverBinType::Bins, val.get()));
    cg->addCoverpoint(cp1);

    cg->finalize();
    ASSERT_EQ(cp1->getNumBins(ModelCoverBinType::Bins), 1);
    ASSERT_EQ(cp1->getBinHits(ModelCoverBinType::Bins, 0), 0);
    ASSERT_EQ(cp1->getCoverage(), 0.0);
    ASSERT_EQ(cg->getCoverage(), 0.0);

    val_e->val()->set_val_u(1, 32); // non-target value
    cg->sample();
    ASSERT_EQ(cp1->getBinHits(ModelCoverBinType::Bins, 0), 0);
    ASSERT_EQ(cp1->getCoverage(), 0.0);
    ASSERT_EQ(cg->getCoverage(), 0.0);

    val_e->val()->set_val_u(10, 32); // non-target value
    cg->sample();
    ASSERT_EQ(cp1->getBinHits(ModelCoverBinType::Bins, 0), 1);
    ASSERT_EQ(cp1->getCoverage(), 100.0);
    ASSERT_EQ(cg->getCoverage(), 100.0);

}

}
}
