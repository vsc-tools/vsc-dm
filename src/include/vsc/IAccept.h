/*
 * IAccept.h
 *
 *  Created on: Aug 2, 2020
 *      Author: ballance
 */

#pragma once
#include <memory>
#include "IVisitor.h"

namespace vsc {

class IAccept {
public:
	virtual ~IAccept() { }

	virtual void accept(IVisitor *v) = 0;

};

}
