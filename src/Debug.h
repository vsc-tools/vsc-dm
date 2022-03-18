/*
 * Debug.h
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#pragma once
#include <string>

#define DEBUG_SCOPE(scope) static vsc::Debug __dbg(#scope)
#define DEBUG_ENTER_BASE(scope, fmt, ...) if (__dbg.en()) __dbg.enter(fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE_BASE(scope, fmt, ...) if (__dbg.en()) __dbg.leave(fmt, ##__VA_ARGS__)
#define DEBUG_BASE(scope, fmt, ...) if (__dbg.en()) __dbg.debug(fmt, ##__VA_ARGS__)

//#define DEBUG_ENTER_BASE(scope, fmt, ...) \
//	fprintf(stdout, "--> " #scope "::" fmt "\n", ##__VA_ARGS__)
//#define DEBUG_LEAVE_BASE(scope, fmt, ...) \
//	fprintf(stdout, "<-- " #scope "::" fmt "\n", ##__VA_ARGS__)
//#define DEBUG_BASE(scope, fmt, ...) \
//	fprintf(stdout, #scope ": " fmt "\n", ##__VA_ARGS__)

namespace vsc {

class DebugMgr;
class Debug {
public:
	Debug(const char *name);

	virtual ~Debug();

	inline bool en() const { return m_en; }

	void set_en(bool en) { m_en = en; }

	const std::string &name() const { return m_name; }

	void enter(const char *fmt, ...);

	void leave(const char *fmt, ...);

	void debug(const char *fmt, ...);

private:
	bool			m_en;
	std::string		m_name;
	DebugMgr		*m_mgr;

};

} /* namespace vsc */

