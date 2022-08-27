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
	m_en = false;
}

DebugMgr::~DebugMgr() {
	// TODO Auto-generated destructor stub
}

void DebugMgr::enable(bool en) {
	m_en = en;

	for (std::unordered_map<std::string,IDebug*>::const_iterator
		it=m_debug_ep_m.begin();
		it!=m_debug_ep_m.end(); it++) {
		if (en != it->second->en()) {
			fprintf(stdout, "DebugMgr: %s %s\n", (en)?"Enable":"Disable", it->second->name().c_str());
		}
		it->second->set_en(m_en);
	}
}

void DebugMgr::addDebug(IDebug *dbg) {
	m_debug_ep_m.insert({dbg->name(), dbg});
	dbg->set_en(m_en);
}

IDebug *DebugMgr::findDebug(const std::string &name) {
	std::unordered_map<std::string,IDebug*>::const_iterator it;

	it = m_debug_ep_m.find(name);

	if (it != m_debug_ep_m.end()) {
		return it->second;
	} else {
		Debug *dbg = new Debug(name);
		m_debug_ep_m.insert({name, dbg});
		return dbg;
	}
}

void DebugMgr::setFlags(
			const std::unordered_map<std::string, int32_t> &flags) {

}

void DebugMgr::enter(IDebug *dbg, const char *fmt, va_list ap) {
	fprintf(stdout, "--> %s::", dbg->name().c_str());
	vfprintf(stdout, fmt, ap);
	fputs("\n", stdout);
}

void DebugMgr::leave(IDebug *dbg, const char *fmt, va_list ap) {
	fprintf(stdout, "<-- %s::", dbg->name().c_str());
	vfprintf(stdout, fmt, ap);
	fputs("\n", stdout);
}

void DebugMgr::debug(IDebug *dbg, const char *fmt, va_list ap) {
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
