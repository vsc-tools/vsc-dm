
#include "TestTaskResolveModelExprVal.h"
#include "vsc/dm/impl/TaskResolveModelExprVal.h"
#include "Context.h"

namespace vsc {
namespace dm {

TEST_F(TestTaskResolveModelExprVal, smoke) {
    IDataTypeInt *vsc_uint32_t = m_ctxt->mkDataTypeInt(false, 32);
    m_ctxt->addDataTypeInt(vsc_uint32_t);

    IModelField *a = m_ctxt->mkModelFieldRoot(vsc_uint32_t, "a");
#ifdef UNDEFINED
    a->val()->set_val_u(1);
#endif

    IModelVal *val_1 = m_ctxt->mkModelVal();
    val_1->set_val_u(1, 15);
    IModelExprUP true_e(m_ctxt->mkModelExprBin(
        m_ctxt->mkModelExprFieldRef(a),
        BinOp::Eq,
        m_ctxt->mkModelExprVal(val_1)
    ));

    IModelVal *val_7 = m_ctxt->mkModelVal();
    val_7->set_val_u(7, 15);
    IModelExprUP false_e(m_ctxt->mkModelExprBin(
        m_ctxt->mkModelExprFieldRef(a),
        BinOp::Eq,
        m_ctxt->mkModelExprVal(val_7)
    ));

    IModelValUP res_1(m_ctxt->mkModelVal());
#ifdef UNDEFINED
    TaskResolveModelExprVal(m_ctxt.get()).eval(
        res_1.get(),
        true_e.get());
#endif
    ASSERT_EQ(res_1->val_u(), 1);

    IModelValUP res_2(m_ctxt->mkModelVal());
#ifdef UNDEFINED
    TaskResolveModelExprVal(m_ctxt.get()).eval(
        res_2.get(),
        false_e.get());
#endif
    ASSERT_EQ(res_2->val_u(), 0);
}

}
}
