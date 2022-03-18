/*
 * IDebugMgr.h
 *
 *  Created on: Mar 16, 2022
 *      Author: mballance
 */
#pragma once
#include <unordered_map>

namespace vsc {

class IDebugMgr {
public:

	virtual ~IDebugMgr() { }

	virtual void setFlags(
			const std::unordered_map<std::string, int32_t> &flags) = 0;

};

}

