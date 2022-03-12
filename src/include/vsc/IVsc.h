/*
 * IVsc.h
 *
 *  Created on: Feb 4, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IContext.h"

namespace vsc {

class IVsc {
public:
	virtual ~IVsc() { }

	virtual IContext *mkContext() = 0;

};

}

