
#include "TestImplCompile.h"

#include "vsc/dm/impl/ContextDelegator.h"
#include "vsc/dm/impl/VisitorBase.h"
#include "vsc/dm/impl/VisitorDelegator.h"

namespace vsc {
namespace dm {

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
}
