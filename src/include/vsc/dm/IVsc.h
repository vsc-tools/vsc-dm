/*
 * IVsc.h
 *
 *  Created on: Feb 4, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/dm/IContext.h"
#include "dmgr/IDebugMgr.h"

namespace vsc {
namespace dm {

class IVsc;
using IVscUP=UP<IVsc>;
class IVsc {
public:
	virtual ~IVsc() { }

	virtual IContext *mkContext() = 0;

	virtual dmgr::IDebugMgr *getDebugMgr() = 0;

};

}
}

