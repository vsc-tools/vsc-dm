/*
 * DebugMgr.h
 *
 *  Created on: Mar 16, 2022
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include <stdarg.h>
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "vsc/IDebugMgr.h"

namespace vsc {

class Debug;

class DebugMgr;
using DebugMgrUP=std::unique_ptr<DebugMgr>;
class DebugMgr : public IDebugMgr {
public:
	DebugMgr();

	virtual ~DebugMgr();

	void addDebug(Debug *dbg);

	virtual void setFlags(
			const std::unordered_map<std::string, int32_t> &flags) override;

	void enter(Debug *dbg, const char *fmt, va_list ap);

	void leave(Debug *dbg, const char *fmt, va_list ap);

	void debug(Debug *dbg, const char *fmt, va_list ap);

	static DebugMgr *inst();

private:
	std::unordered_map<std::string, int32_t>		m_debug_en_m;
	std::unordered_map<std::string, Debug *>		m_debug_ep_m;

	static DebugMgrUP								m_inst;
};

} /* namespace vsc */

