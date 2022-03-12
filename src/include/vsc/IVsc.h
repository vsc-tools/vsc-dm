/*
 * IVsc.h
 *
 *  Created on: Feb 4, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IContext.h"

namespace vsc {

class IVsc;
using IVscUP=std::unique_ptr<IVsc>;
class IVsc {
public:
	virtual ~IVsc() { }

	virtual IContext *mkContext() = 0;

};

}

