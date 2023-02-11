/*
 * VscTestBase.cpp
 *
 *  Created on: Oct 6, 2021
 *      Author: mballance
 */
#include "dmgr/FactoryExt.h"
#include "vsc/dm/FactoryExt.h"
#include "VscTestBase.h"

namespace vsc {
namespace dm {

VscTestBase::VscTestBase() {
	// TODO Auto-generated constructor stub

}

VscTestBase::~VscTestBase() {
	// TODO Auto-generated destructor stub
}

void VscTestBase::SetUp() {
    dmgr::IFactory *dmgr_f = dmgr_getFactory();
    m_factory = vsc_dm_getFactory();
    m_factory->init(dmgr_f->getDebugMgr());
    m_ctxt = IContextUP(m_factory->mkContext());
}

void VscTestBase::TearDown() {
}

void VscTestBase::enableDebug(bool en) {
    dmgr::IFactory *dmgr_f = dmgr_getFactory();
    dmgr_f->getDebugMgr()->enable(en);
}

}
} /* namespace vsc */
