/*
 * IVisitorTask.h
 *
 *  Created on: Mar 23, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IAccept.h"

namespace vsc {
namespace dm {

class ITask {
public:

	virtual ~ITask() { }

	virtual void apply(IAccept *item) = 0;
};

}
}

