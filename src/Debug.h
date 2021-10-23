/*
 * Debug.h
 *
 *  Created on: Oct 23, 2021
 *      Author: mballance
 */

#pragma once

#define DEBUG_SCOPE(scope)
#define DEBUG_ENTER_BASE(scope, fmt, ...) \
	fprintf(stdout, "--> " #scope "::" fmt "\n", ##__VA_ARGS__)
#define DEBUG_LEAVE_BASE(scope, fmt, ...) \
	fprintf(stdout, "<-- " #scope "::" fmt "\n", ##__VA_ARGS__)
#define DEBUG_BASE(scope, fmt, ...) \
	fprintf(stdout, #scope ": " fmt "\n", ##__VA_ARGS__)

namespace vsc {

class Debug {
public:
	Debug();

	virtual ~Debug();
};

} /* namespace vsc */

