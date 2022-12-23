/*
 * Vsc.h
 *
 *  Created on: Feb 4, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IVsc.h"

namespace vsc {
namespace dm {

class VscImpl : public IVsc {
public:
	VscImpl();

	virtual ~VscImpl();

	virtual IContext *mkContext() override;

	virtual IDebugMgr *getDebugMgr() override;

	static IVsc *inst();

private:
	static IVscUP			m_inst;

};

}
} /* namespace vsc */


