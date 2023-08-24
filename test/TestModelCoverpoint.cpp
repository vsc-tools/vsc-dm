
#include "TestModelCoverpoint.h"

namespace vsc {
namespace dm {

TEST_F(TestModelCoverpoint, single_cp_single_bin) {

    IModelCovergroupUP cg(m_ctxt->mkModelCovergroup("cg"));
    IModelValUP val(m_ctxt->mkModelVal());
    IModelExprVal *val_e = m_ctxt->mkModelExprVal(val.get());
    IModelCoverpoint *cp1 = m_ctxt->mkModelCoverpoint(
        "cp1",
        m_ctxt->mkModelCoverpointTargetExpr(val_e, 32),
        0);
    val->set_val_u(10, 32);
    cp1->addBin(m_ctxt->mkModelCoverBinSingleVal("b", ModelCoverBinType::Bins, val.get()));
    cg->addCoverpoint(cp1);

    cg->finalize();
    ASSERT_EQ(cp1->getNumBins(ModelCoverBinType::Bins), 1);
    ASSERT_EQ(cp1->getBinHits(ModelCoverBinType::Bins, 0), 0);
    ASSERT_EQ(cp1->getCoverage(), 0.0);
    ASSERT_EQ(cg->getCoverage(), 0.0);

#ifdef UNDEFINED
    val_e->val()->set_val_u(1, 32); // non-target value
#endif
    cg->sample();
    ASSERT_EQ(cp1->getBinHits(ModelCoverBinType::Bins, 0), 0);
    ASSERT_EQ(cp1->getCoverage(), 0.0);
    ASSERT_EQ(cg->getCoverage(), 0.0);

#ifdef UNDEFINED
    val_e->val()->set_val_u(10, 32); // non-target value
#endif
    cg->sample();
    ASSERT_EQ(cp1->getBinHits(ModelCoverBinType::Bins, 0), 1);
    ASSERT_EQ(cp1->getCoverage(), 100.0);
    ASSERT_EQ(cg->getCoverage(), 100.0);

}

}
}
