/*
 * Vsc.h
 *
 *  Created on: Feb 4, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IVsc.h"

namespace vsc {

class VscImpl : public IVsc {
public:
	VscImpl();

	virtual ~VscImpl();

	virtual IContext *mkContext() override;

	static IVsc *inst();

private:
	static IVscUP			m_inst;

};

} /* namespace vsc */


