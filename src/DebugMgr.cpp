/*
 * DebugMgr.cpp
 *
 *  Created on: Mar 16, 2022
 *      Author: mballance
 */

#include "DebugMgr.h"
#include "Debug.h"

namespace vsc {

DebugMgr::DebugMgr() {
	// TODO Auto-generated constructor stub

}

DebugMgr::~DebugMgr() {
	// TODO Auto-generated destructor stub
}

void DebugMgr::addDebug(Debug *dbg) {
	m_debug_ep_m.insert({dbg->name(), dbg});
//	dbg->set_en(true);
}

void DebugMgr::setFlags(
			const std::unordered_map<std::string, int32_t> &flags) {

}

void DebugMgr::enter(Debug *dbg, const char *fmt, va_list ap) {
	fprintf(stdout, "--> %s::", dbg->name().c_str());
	vfprintf(stdout, fmt, ap);
	fputs("\n", stdout);
}

void DebugMgr::leave(Debug *dbg, const char *fmt, va_list ap) {
	fprintf(stdout, "<-- %s::", dbg->name().c_str());
	vfprintf(stdout, fmt, ap);
	fputs("\n", stdout);
}

void DebugMgr::debug(Debug *dbg, const char *fmt, va_list ap) {
	fprintf(stdout, "%s: ", dbg->name().c_str());
	vfprintf(stdout, fmt, ap);
	fputs("\n", stdout);
}

DebugMgr *DebugMgr::inst() {
	if (!m_inst) {
		m_inst = DebugMgrUP(new DebugMgr());
	}
	return m_inst.get();
}

DebugMgrUP DebugMgr::m_inst;

} /* namespace vsc */
