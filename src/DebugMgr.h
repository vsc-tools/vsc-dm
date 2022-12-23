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
#include "vsc/dm/IDebug.h"
#include "vsc/dm/IDebugMgr.h"

namespace vsc {
namespace dm {

class Debug;

class DebugMgr;
using DebugMgrUP=std::unique_ptr<DebugMgr>;
class DebugMgr : public IDebugMgr {
public:
	DebugMgr();

	virtual ~DebugMgr();

	virtual void enable(bool en) override;

	virtual void addDebug(IDebug *dbg) override;

	virtual IDebug *findDebug(const std::string &name) override;

	virtual void setFlags(
			const std::unordered_map<std::string, int32_t> &flags) override;

	virtual void enter(IDebug *dbg, const char *fmt, va_list ap) override;

	virtual void leave(IDebug *dbg, const char *fmt, va_list ap) override;

	virtual void debug(IDebug *dbg, const char *fmt, va_list ap) override;

	static DebugMgr *inst();

private:
	bool											m_en;
	std::unordered_map<std::string, int32_t>		m_debug_en_m;
	std::unordered_map<std::string, IDebug *>		m_debug_ep_m;

	static DebugMgrUP								m_inst;
};

}
} /* namespace vsc */

