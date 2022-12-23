
#ifndef INCLUDED_DEBUG_MACROS_H
#define INCLUDED_DEBUG_MACROS_H
#include "vsc/dm/IDebug.h"

#define DEBUG_INIT(scope, mgr) \
    if (!m_dbg) { \
        m_dbg = ((mgr))?(mgr)->findDebug(scope):0; \
    }
#define DEBUG_ENTER(fmt, ...) \
    if (m_dbg && m_dbg->en()) m_dbg->enter(fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) \
    if (m_dbg && m_dbg->en()) m_dbg->leave(fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) \
    if (m_dbg && m_dbg->en()) m_dbg->debug(fmt, ##__VA_ARGS__)

#endif
