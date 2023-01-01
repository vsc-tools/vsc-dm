/*
 * Vsc.cpp
 *
 *  Created on: Feb 4, 2022
 *      Author: mballance
 */

#include "Context.h"
#include "VscImpl.h"

namespace vsc {
namespace dm {

VscImpl::VscImpl() {
	// TODO Auto-generated constructor stub

}

VscImpl::~VscImpl() {
	// TODO Auto-generated destructor stub
}

IContext *VscImpl::mkContext() {
	return new Context(0);
}

dmgr::IDebugMgr *VscImpl::getDebugMgr() {
    // TODO:
    return 0;
}

IVsc *VscImpl::inst() {
	if (!m_inst) {
		m_inst = IVscUP(new VscImpl());
	}
	return m_inst.get();
}

IVscUP VscImpl::m_inst;

}
} /* namespace vsc */

extern "C" vsc::dm::IVsc *ivsc() {
	return vsc::dm::VscImpl::inst();
}
