/*
 * Vsc.cpp
 *
 *  Created on: Feb 4, 2022
 *      Author: mballance
 */

#include "VscImpl.h"

namespace vsc {

VscImpl::VscImpl() {
	// TODO Auto-generated constructor stub

}

VscImpl::~VscImpl() {
	// TODO Auto-generated destructor stub
}

IVsc *VscImpl::inst() {
	if (!m_inst) {
		m_inst = IVscUP(new VscImpl());
	}
	return m_inst.get();
}

IVscUP VscImpl::m_inst;

} /* namespace vsc */

extern "C" vsc::IVsc *ivsc() {
	return vsc::VscImpl::inst();
}
