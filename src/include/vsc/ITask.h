/*
 * IVisitorTask.h
 *
 *  Created on: Mar 23, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IAccept.h"

namespace vsc {

class ITask {
public:

	virtual ~ITask() { }

	virtual void apply(IAccept *item) = 0;
};


}

