/*
 * IDebugMgr.h
 *
 *  Created on: Mar 16, 2022
 *      Author: mballance
 */
#pragma once
#include <unordered_map>
#include "vsc/dm/IDebug.h"

namespace vsc {
namespace dm {

class IDebugMgr {
public:

	virtual ~IDebugMgr() { }

	virtual void setFlags(
			const std::unordered_map<std::string, int32_t> &flags) = 0;

	virtual void enable(bool en) = 0;

	virtual void addDebug(IDebug *dbg) = 0;

	virtual IDebug *findDebug(const std::string &name) = 0;

	virtual void enter(IDebug *dbg, const char *fmt, va_list ap) = 0;
	virtual void leave(IDebug *dbg, const char *fmt, va_list ap) = 0;
	virtual void debug(IDebug *dbg, const char *fmt, va_list ap) = 0;

};

}
}

