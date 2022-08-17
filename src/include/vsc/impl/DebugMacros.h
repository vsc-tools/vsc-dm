
#ifndef INCLUDED_DEBUG_MACROS_H
#define INCLUDED_DEBUG_MACROS_H
#include "vsc/IDebug.h"

#ifndef DEBUG_MGR_REF
#error Must define DEBUG_MGR_REF to an expression that returns IDebugMgr
#endif

static vsc::IDebug *__dbg = 0;
#define DEBUG_INIT(scope) \
    if (!__dbg) { \
        __dbg = ((DEBUG_MGR_REF))?(DEBUG_MGR_REF)->findDebug(scope):0 \
    }
#define DEBUG_ENTER_BASE(fmt, ...) \
    if (__dbg && __dbg->en()) __dbg->enter(fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE_BASE(fmt, ...) \
    if (__dbg && __dbg->en()) __dbg->leave(fmt, ##__VA_ARGS__)
#define DEBUG_BASE(fmt, ...) \
    if (__dbg && __dbg->en()) __dbg.debug(fmt, ##__VA_ARGS__)

#endif
