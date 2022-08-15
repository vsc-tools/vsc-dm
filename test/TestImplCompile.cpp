
#include "TestImplCompile.h"

#include "vsc/impl/ContextDelegator.h"
#include "vsc/impl/VisitorBase.h"
#include "vsc/impl/VisitorDelegator.h"

namespace vsc {

TEST_F(TestImplCompile, context_delegator) {
    ContextDelegator ctxt_dlg(0);
}

TEST_F(TestImplCompile, visitor_base) {
    VisitorBase visitor;
}

TEST_F(TestImplCompile, visitor_delegator) {
    VisitorDelegator visitor_dlg(0);
}

}