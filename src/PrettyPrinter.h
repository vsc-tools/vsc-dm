/*
 * PrettyPrinter.h
 *
 *  Created on: Oct 5, 2021
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/impl/VisitorBase.h"

namespace vsc {
namespace dm {

class PrettyPrinter : public VisitorBase {
public:
	PrettyPrinter();
	virtual ~PrettyPrinter();
};

}
} /* namespace vsc */

